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

AppStatus gAppStatus = RUNNING;

void initialize();
void processInput();
void update();
void render();
void shutdown();

void initialize() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello raylib!");
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
