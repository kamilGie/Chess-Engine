#include "ChessAI.hpp"
#include "../chessboard/chessboard.hpp"
#include "../move/move.hpp"

ChessAI::ChessAI() {
}

ChessAI::~ChessAI() {
}

Move* ChessAI::GetMove(Chessboard& chessboard) {
    return  new Move({0, 1}, {0, 3},chessboard);;
}