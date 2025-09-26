/**
 * Author: Perry Huang
 * Assignment: Simple 2D Scene
 * Date due: 2025-09-27, 11:59pm
 * I pledge that I have completed this assignment without
 * collaborating with anyone else, in conformance with the
 * NYU School of Engineering Policies and Procedures on
 * Academic Misconduct.
 */

#include <math.h>

#include "raylib.h"

enum AppStatus { RUNNING, TERMINATED };
enum ScaleDirection { INCREASING = 1, DECREASING = -1 };

constexpr int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 450, FPS = 60, SIDES = 4;
constexpr char DEFECT_FP[] = "assets/defect.png";
constexpr char DARKORB_FP[] = "assets/darkOrb.png";
constexpr char DONU_FP[] = "assets/donu.png";
constexpr Vector2 FIRST_THIRD = {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.0f};
constexpr Vector2 SECOND_THIRD = {2.0f * SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.0f};
constexpr Vector2 BASE_SIZE = {200.0f, 200.0f};
constexpr float MAX_AMP = 50.0f;

Texture2D gDefect;
Texture2D gDarkOrb;
Texture2D gDonu;

Vector2 gDefectPos = FIRST_THIRD;
Vector2 gOrbPos = gDefectPos;
Vector2 gDonuPos = SECOND_THIRD;

// characters scale the same
Vector2 gScale = BASE_SIZE;
Vector2 gOrbScale = {70.0f, 70.0f};
float gPreviousTicks = 0.0f;

Color gBackgroundColor[4] = {WHITE, LIGHTGRAY, BLUE, VIOLET};
int gBackgroundIndex = 0;
float gFrameNum = 0.0f;

AppStatus gAppStatus = RUNNING;
ScaleDirection gScaleDirection = INCREASING;

void initialize();
void processInput();
void update();
void render();
void shutdown();

void initialize() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello raylib!");

    gDefect = LoadTexture(DEFECT_FP);
    gDarkOrb = LoadTexture(DARKORB_FP);
    gDonu = LoadTexture(DONU_FP);

    SetTargetFPS(FPS);
}

void processInput() {
    if (WindowShouldClose()) {
        gAppStatus = TERMINATED;
    }
}

void update() {
    gFrameNum += 1.0f;
    if (gFrameNum > 200.0f) {
        gFrameNum = 0;
        gBackgroundIndex = (gBackgroundIndex + 1) % 4;
    }

    float ticks = (float)GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;
    if (gOrbScale.x > 200.0f) {
        gScaleDirection = DECREASING;
    } else if (gOrbScale.x < 70.0f) {
        gScaleDirection = INCREASING;
    }
    gOrbScale.x += gScaleDirection * 15.0f * deltaTime;
    gOrbScale.y += gScaleDirection * 15.0f * deltaTime;

    gDefectPos.x = FIRST_THIRD.x + MAX_AMP * std::cos(ticks);
    gDefectPos.y = FIRST_THIRD.y + MAX_AMP / 4.0f * std::sin(ticks);

    gOrbPos.x = gDefectPos.x + MAX_AMP * 3 * std::cos(ticks);
    gOrbPos.y = gDefectPos.y + MAX_AMP * 3 * std::sin(ticks);

    gDonuPos.x = SECOND_THIRD.x + MAX_AMP * std::cos(ticks);
    // -1 makes it so that donu moves in positive y
    gDonuPos.y = SECOND_THIRD.y + MAX_AMP / 4.0f * -1 * std::abs(std::sin(ticks));
}

void render() {
    BeginDrawing();
    ClearBackground(gBackgroundColor[gBackgroundIndex]);
    Rectangle defectArea = {0.0f, 0.0f, static_cast<float>(gDefect.width), static_cast<float>(gDefect.height)};
    Rectangle darkOrbArea = {0.0f, 0.0f, static_cast<float>(gDarkOrb.width), static_cast<float>(gDarkOrb.height)};
    Rectangle donuArea = {0.0f, 0.0f, static_cast<float>(gDonu.width), static_cast<float>(gDonu.height)};

    // first 1/3 of screen
    Rectangle defectDest = {gDefectPos.x, gDefectPos.y, gScale.x, gScale.y};

    // surrounds defect
    Rectangle darkOrbDest = {
        gOrbPos.x,
        gOrbPos.y,
        gOrbScale.x,
        gOrbScale.y,
    };

    // 2nd third of screen
    Rectangle donuDest = {gDonuPos.x, gDonuPos.y, gScale.x, gScale.y};

    Vector2 defectOrigin = {
        gScale.x / 2.0f,
        gScale.y / 2.0f,
    };
    Vector2 darkOrbOrigin = {
        gOrbScale.x / 2.0f,
        gOrbScale.y / 2.0f,
    };
    Vector2 donuOrigin = {
        gScale.x / 2.0f,
        gScale.y / 2.0f,
    };

    DrawTexturePro(gDonu, donuArea, donuDest, donuOrigin, 0.0f, WHITE);
    DrawTexturePro(gDefect, defectArea, defectDest, defectOrigin, 0.0f, WHITE);
    DrawTexturePro(gDarkOrb, darkOrbArea, darkOrbDest, darkOrbOrigin, 0.0f, WHITE);

    EndDrawing();
}

void shutdown() {
    CloseWindow();
}

int main() {
    initialize();
    while (gAppStatus == RUNNING) {
        processInput();
        update();
        render();
    }
    shutdown();
    return 0;
}
