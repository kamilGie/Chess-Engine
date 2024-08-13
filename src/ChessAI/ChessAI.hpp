#pragma once
#include <raylib.h>

#include <memory>

class Move;
class Chessboard;
class Piece;
enum class PieceColor;

class ChessAI {
   public:
    explicit ChessAI(PieceColor colorAI);
    ~ChessAI();
    Move* GetMove(Chessboard& chessboard) ;

    PieceColor colorAI;

private:
    static float CalculateMove(Vector2 from, Vector2 to, std::array<std::shared_ptr<Piece>, 64> grid, PieceColor colorTurn, int depth=0);
};