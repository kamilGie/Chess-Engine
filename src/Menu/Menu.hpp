#pragma once

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
    int fps;
    bool ChessAI;
    bool AIBlack;
    bool hasSettingsChanged=false;
};