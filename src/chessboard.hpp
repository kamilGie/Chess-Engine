#pragma once
#include <raylib.h>

#include <iostream>

#include "colors.hpp"
#include "piece_interfaces.hpp"

extern int cellSize;

class Chessboard {
   public:
    Chessboard();
    void Draw();
    void ShowSquares();
    int cellCount = 8;
    Piece* grid[8][8]{};
    Vector2 lastMovePositions[2]{{9, 9}, {9, 9}};

   private:
};