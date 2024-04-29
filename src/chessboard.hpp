#pragma once
#include <raylib.h>
#include <iostream>
#include "piece.hpp"

extern int cellSize;

class Chessboard {
   public:
    Chessboard();
    void Draw();
    void ShowSquares();
    int cellCount = 8;
    Piece* grid[8][8];

   private:
};