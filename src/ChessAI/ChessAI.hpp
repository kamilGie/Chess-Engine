#pragma once

class Move;
class Chessboard;
enum class PieceColor;

class ChessAI{
public:
    ChessAI(PieceColor colorAI);
    ~ChessAI();
    Move* GetMove(Chessboard& chessboard);
    PieceColor colorAI;
};