#pragma once

extern int cellSize;

class Chessboard {
   public:
    Chessboard();
    void Draw();
    int cellCount = 8;
    int grid[8][8];

   private:
};