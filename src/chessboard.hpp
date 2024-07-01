#pragma once
#include <raylib.h>

#include <iostream>

#include "colors.hpp"
#include "piece_interfaces.hpp"

extern int cellSize;

class Chessboard {
   public:
    Chessboard();
    void DrawPieces();
    void DrawSquares();
    void DrawLegalMoves(std::shared_ptr<Piece> piece);
    void DrawSelectedPieceDetails(std::shared_ptr<Piece> piece);
    int cellCount = 8;
    std::shared_ptr<Piece> grid[8][8]{};
    Vector2 lastMovePositions[2]{{9, 9}, {9, 9}};

   private:
};