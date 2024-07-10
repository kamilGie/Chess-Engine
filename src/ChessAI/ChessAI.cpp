#include "ChessAI.hpp"
#include "../chessboard/chessboard.hpp"
#include "../move/move.hpp"
#include "../pieces/bases/piece.hpp"



ChessAI::ChessAI(PieceColor colorAI):colorAI(colorAI) { }

ChessAI::~ChessAI() {
}

Move* ChessAI::GetMove(Chessboard& chessboard) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessboard.grid[i][j] && chessboard.grid[i][j]->color == colorAI) {
                for (auto& move : chessboard.grid[i][j]->legalMoves) {
                        return new Move({(float)i, (float)j}, move,chessboard);
                }
            }
        }
    }
    return nullptr;
}