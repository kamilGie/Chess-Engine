#include "launcher.hpp"
#include <raylib.h>
#include <fstream>
#include <iostream>

Launcher::Launcher() {
    InitWindow(300, 500, "chess launcher");
    SetTargetFPS(60);
}

Launcher::~Launcher() {
    CloseWindow();
    //if(!hasSettingsChanged) return;

    std::ofstream file("../src/GameSettings.txt");
    if (file.is_open()) {
        file << "ChessAI true\n";
        file << "ChessAIColor black\n";
        file << "TargetFPS 120\n";
        file.close();
    }
}

void Launcher::Draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
}

void Launcher::Update() {
}

void Launcher::HandleInput() {

}
