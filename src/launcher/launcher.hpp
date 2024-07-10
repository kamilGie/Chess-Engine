#pragma once

class Launcher {
   public:
    Launcher();
    ~Launcher();
    void Draw();
    void Update();
    void HandleInput();
    private:
    int fps;
    bool ChessAI;
    bool AIBlack;
    bool hasSettingsChanged;
};