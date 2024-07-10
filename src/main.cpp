#include "game.hpp"
#include "launcher/launcher.hpp"

int main() {
    {
        Launcher launcher;
        while (!WindowShouldClose() && !launcher.start) {
            launcher.HandleInput();
            launcher.Update();
            launcher.Draw();
        }
    }

    Game game;
    while (!WindowShouldClose()) {
        game.HandleInput();
        game.Update();
        game.Draw();
    }
    CloseWindow();
}