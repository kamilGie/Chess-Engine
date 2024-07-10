#include "ChessAI.hpp"
#include "../chessboard/chessboard.hpp"
#include "../move/move.hpp"
#include "../pieces/bases/piece.hpp"



ChessAI::ChessAI(PieceColor colorAI):colorAI(colorAI) { }

ChessAI::~ChessAI() {
}

Move* ChessAI::GetMove(Chessboard& chessboard) {

    return  new Move({0, 1}, {0, 3},chessboard);
}