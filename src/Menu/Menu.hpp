#pragma once
#include <raylib.h>

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

    Rectangle startButton = { (float)GetScreenWidth() / 2 - 140, (float)GetScreenHeight() - 100, 280, 50 };
    bool startButtonHover = false;

    Rectangle PvP = { (float)GetScreenWidth() / 4 - 100-50,  200, 200, 50 };
    bool PvPHover = false;

    Rectangle PvAI = { (float)GetScreenWidth() / 2 - 100,  200, 200, 50 };
    bool PvAIHover = false;

    Rectangle AIvsAI = { ((float)GetScreenWidth() / 4 *3) - 100+50,  200, 200, 50 };
    bool AIvsAIHover = false;

    int fps;
    bool isPVP=false;
    bool isPvAI=false;
    bool isAIvsAI=false;
    bool isAIBlack=false;
    bool hasSettingsChanged=false;

    Texture2D MenuBackground;
};