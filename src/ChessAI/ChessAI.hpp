#pragma once
#include <raylib.h>

#include <memory>

class Move;
class Chessboard;
class Piece;
enum class PieceColor;

class ChessAI {
   public:
    ChessAI(PieceColor colorAI);
    ~ChessAI();
    Move* GetMove(Chessboard& chessboard);
    PieceColor colorAI;
};