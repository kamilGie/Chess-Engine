#pragma once
#include <raylib.h>
#include <memory>

class Move;
class Chessboard;
class Piece;
enum class PieceColor;

class ChessAI{
public:
    ChessAI(PieceColor colorAI);
    ~ChessAI();
    Move* GetMove(Chessboard& chessboard);
    PieceColor colorAI;
private:
    float CalculateMove(Vector2 from , Vector2 to, std::shared_ptr<Piece> (&grid)[8][8],PieceColor,int depth=0);
};