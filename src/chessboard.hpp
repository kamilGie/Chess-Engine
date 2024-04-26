#pragma once

class Chessboard {
   public:
    Chessboard();
    void Draw();
    int cellCount = 8;
    int cellSize = 100;
    int grid[8][8];

   private:
};