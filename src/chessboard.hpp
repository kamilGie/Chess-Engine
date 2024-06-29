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
    std::shared_ptr<Piece> grid[8][8]{};
    Vector2 lastMovePositions[2]{{9, 9}, {9, 9}};
    bool atackedByWhite[8][8];
    bool atackedByBlack[8][8];

   private:
};