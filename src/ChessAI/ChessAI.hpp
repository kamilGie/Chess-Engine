#pragma once

class Move;
class Chessboard;

class ChessAI{
public:
    ChessAI();
    ~ChessAI();
    Move* GetMove(Chessboard& chessboard);
};