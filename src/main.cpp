#include <raylib.h>
#include <iostream>
#include "game.hpp"

using namespace std;

int main() {
    const int windowWidth = 800;
    const int windowHeight = 800;

    InitWindow(windowHeight, windowWidth, "chess");
    SetTargetFPS(120);

    Game game;

    while (!WindowShouldClose()) {
        BeginDrawing();
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}