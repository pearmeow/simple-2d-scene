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

constexpr int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 450, FPS = 60, SIDES = 4;
constexpr char DEFECT_FP[] = "assets/defect.png";
constexpr char DARKORB_FP[] = "assets/darkOrb.png";
constexpr char DONU_FP[] = "assets/donu.png";

Texture2D gDefect;
Texture2D gDarkOrb;
Texture2D gDonu;

constexpr Vector2 FIRST_THIRD = {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.0f};
constexpr Vector2 SECOND_THIRD = {2.0f * SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.0f};
constexpr Vector2 BASE_SIZE = {200.0f, 200.0f};

Vector2 gDefectPos = FIRST_THIRD;
Vector2 gOrbPos = gDefectPos;
Vector2 gDonuPos = SECOND_THIRD;

// both of them are going to scale the same
Vector2 gScale = BASE_SIZE;
Vector2 gOrbScale = {50.0f, 50.0f};

AppStatus gAppStatus = RUNNING;

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
    // do some time based changes here
}

void render() {
    BeginDrawing();
    ClearBackground(WHITE);
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

    DrawTexturePro(gDefect, defectArea, defectDest, defectOrigin, 0.0f, WHITE);
    DrawTexturePro(gDarkOrb, darkOrbArea, darkOrbDest, darkOrbOrigin, 0.0f, WHITE);
    DrawTexturePro(gDonu, donuArea, donuDest, donuOrigin, 0.0f, WHITE);

    // use a texture
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
