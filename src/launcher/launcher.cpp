#include "launcher.hpp"

#include <raylib.h>

#include <fstream>

Launcher::Launcher() {
    std::ifstream file("../src/GameSettings.txt");
    std::string text;
    while (file >> text) {
        if (text == "ChessAI") {
            file >> text;
            ChessAI = (text == "true") ? true : false;
        } else if (text == "ChessAIColor") {
            file >> text;
            AIBlack = (text == "black") ? true : false;
        } else if (text == "TargetFPS") {
            file >> fps;
        }
    }
    file.close();

    SetTargetFPS(60);
    InitWindow(300, 500, "chess launcher");
}

Launcher::~Launcher() {
    CloseWindow();
    if (!hasSettingsChanged) return;

    std::ofstream file("../src/GameSettings.txt");
    if (file.is_open()) {
        file << "ChessAI " << (ChessAI ? "true\n" : "false\n");
        file << "ChessAIColor " << (AIBlack ? "black\n" : "white\n");
        file << "TargetFPS " << fps;
        file.close();
    }
}

void Launcher::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Chess AI", 10, 10, 20, BLACK);
    DrawText(ChessAI ? "ON" : "OFF", 200, 10, 20, BLACK);
    if (ChessAI) {
        DrawText("AI Color", 10, 40, 20, BLACK);
        DrawText(AIBlack ? "Black" : "White", 200, 40, 20, BLACK);
    }
    DrawText("Target FPS", 10, 70 - (ChessAI ? 0 : 30), 20, BLACK);
    DrawText(std::to_string(fps).c_str(), 200, 70 - (ChessAI ? 0 : 30), 20, BLACK);

    DrawRectangle(GetScreenWidth() / 2 - 140, GetScreenHeight() - 100, 280, 50, GREEN);
    DrawText("Start Game", GetScreenWidth() / 2 - 100, GetScreenHeight() - 90, 20, BLACK);
    EndDrawing();
}

void Launcher::Update() {
}

void Launcher::HandleInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), {(float)GetScreenWidth() / 2 - 140, (float)GetScreenHeight() - 100, 280, 50})) start = true;
        if (CheckCollisionPointRec(GetMousePosition(), {10, 10, 280, 20})) {
            ChessAI = !ChessAI;
            hasSettingsChanged = true;
        }
        if (ChessAI && CheckCollisionPointRec(GetMousePosition(), {10, 40, 280, 20})) {
            AIBlack = !AIBlack;
            hasSettingsChanged = true;
        }
        if (CheckCollisionPointRec(GetMousePosition(), {10, 70 - float(ChessAI ? 0 : 30), 280, 20})) {
            fps = (fps == 60) ? 120 : 60;
            hasSettingsChanged = true;
        }
    }
}
