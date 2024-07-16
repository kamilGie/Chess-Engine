#pragma once
#include <raylib.h>
#include "MenuButton.hpp"

class Menu {
   public:
    Menu();
    ~Menu();
    void Draw();
    void Update();
    void HandleInput();
    bool running = true;
    bool quit = false;
    private:

    MenuButton startButton = MenuButton({ (float)GetScreenWidth() / 2 - 140, (float)GetScreenHeight() - 100, 280, 50 }, "Start Game");
    MenuButton PvP = MenuButton({ (float)GetScreenWidth() / 4 - 150,  200, 200, 50 }, "PvP");
    MenuButton PvAI = MenuButton({ (float)GetScreenWidth() / 2 - 100,  200, 200, 50 }, "PvAI");
    MenuButton AIvAI = MenuButton({ ((float)GetScreenWidth() / 4 *3) - 50,  200, 200, 50 }, "AIvAI");
    MenuButton AiColor = MenuButton({ (float)GetScreenWidth() / 2 - 100,  140, 200, 50 }, "AI Color");
    Rectangle AiColorMargin = { (float)GetScreenWidth() / 2 -100 ,  140, 200, 60 };

    int fps;
    bool hasSettingsChanged=false;

    Texture2D MenuBackground;
};