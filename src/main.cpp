#include "game.hpp"

int main() {
    InitWindow(800, 800, "chess");
    SetTargetFPS(120);

    Game game;
    while (!WindowShouldClose()) {
        game.HandleInput();
        game.Update();
        game.Draw();
    }

    CloseWindow();
}