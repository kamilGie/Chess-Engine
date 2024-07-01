#pragma once
#include <raylib.h>

#include "colors.hpp"
#include "pieces.hpp"

extern int cellSize;

class Chessboard {
   public:
    Chessboard();
    void initPieces();
    void DrawPieces();
    void DrawSquares();
    void DrawLegalMoves(std::shared_ptr<Piece> piece);
    void DrawSelectedPieceDetails(std::shared_ptr<Piece> piece);
    void SetLastMovePositions(Vector2 from, Vector2 to);
    int cellCount = 8;
    std::shared_ptr<Piece> grid[8][8]{};
    Vector2 lastMovePositions[2]{{9, 9}, {9, 9}};

   private:
};