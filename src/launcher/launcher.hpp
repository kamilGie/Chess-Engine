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
    int fps=60;
    bool ChessAI=true;
    bool AIBlack=true;
    bool hasSettingsChanged=false;
};