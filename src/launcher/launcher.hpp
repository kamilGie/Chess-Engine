#pragma once

class Launcher {
   public:
    Launcher();
    ~Launcher();
    void Draw();
    void Update();
    void HandleInput();
    bool start = false;
    private:
    int fps;
    bool ChessAI;
    bool AIBlack;
    bool hasSettingsChanged=false;
};