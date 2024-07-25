#include "game.hpp"
#include "Menu/Menu.hpp"

int main() {
    InitWindow(800, 800, "chess");
    // for loop to delete Menu object after it's scope
    for (Menu menu;menu.running;){
        menu.HandleInput();
        menu.Update();
        menu.Draw();
        if (WindowShouldClose() || menu.quit) return 0;
    }

    Game game;
    while (!WindowShouldClose()) {
        game.HandleInput();
        game.Update();
        game.Draw();
    }
    CloseWindow();
}