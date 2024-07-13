#pragma once
#include <raylib.h>
#include <array>
#include <memory>

extern int cellSize;

class Piece;

class Chessboard {
   public:
    ~Chessboard();
    void initPieces();
    void DrawPieces();
    void DrawSquares();
    void DrawLegalMoves(std::shared_ptr<Piece> piece);
    void DrawSelectedPieceDetails(std::shared_ptr<Piece> piece);
    void SetLastMovePositions(Vector2 from, Vector2 to);
    int cellCount = 8;
    std::array<std::shared_ptr<Piece>,64> grid{};
    Vector2 lastMovePositions[2]{{9, 9}, {9, 9}};

   private:
};