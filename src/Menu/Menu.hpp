#pragma once
#include <raylib.h>
#include "buttonsDecorators/BD.hpp"


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
    void InitButtons();

    MenuButton startButton = MenuButton({ (float)GetScreenWidth() / 2 - 140, (float)GetScreenHeight() - 100, 280, 50 }, "Start Game", Color{108, 152, 63, 255}, Color{233, 235, 210, 255});
    //MenuButtonsColor<MenuButton> startButton{Color{108, 152, 63, 255}, Color{233, 235, 210, 255}, MenuButton{{(float)GetScreenWidth() / 2 - 140, (float)GetScreenHeight() - 100, 280, 50},  "Start Game"}};
    ButtonStateDecorator<MenuButton> PvP{MenuButton{ { (float)GetScreenWidth() / 4 - 150,  200, 200, 50 }, "PvP"}};
    ButtonStateDecorator<MenuButton> PvAI{MenuButton{ { (float)GetScreenWidth() / 2 - 100,  200, 200, 50 }, "PvAI"}};
    ButtonStateDecorator<MenuButton> AIvAI{MenuButton{ { (float)GetScreenWidth() / 4 * 3 - 50,  200, 200, 50 }, "AIvAI"}};
    ButtonStateDecorator<MenuButton> AiColorBlack = MenuButton({ (float)GetScreenWidth() / 2 - 100,  140, 90,50 }, "Black", BLACK);
    ButtonStateDecorator<MenuButton> AIColorWHite = MenuButton({ (float)GetScreenWidth() / 2 + 10,  140, 90,50 }, "White", WHITE);

    MenuButtonsGroup PvsAIGroup;
    MenuButtonsGroup AllButtons;
    

    int fps;
    bool hasSettingsChanged=false;

    Texture2D MenuBackground;
};