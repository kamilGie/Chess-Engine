#include "ChessAI.hpp"

#include <raymath.h>

#include <memory>
#include <iostream>
#include <unordered_map>

#include "../chessboard/chessboard.hpp"
#include "../move/move.hpp"
#include "../pieces/bases/piece.hpp"
#include "../pieces/models/king/king.hpp"

#include "Façade/calculateMoveFaçade.hpp"

ChessAI::ChessAI(PieceColor colorAI) : colorAI(colorAI) {}

ChessAI::~ChessAI() {}

Move* ChessAI::GetMove(Chessboard& chessboard) {
    double startTime = GetTime();
    std::array<std::shared_ptr<Piece>, 64> GridCoppy;
    for (int i = 0; i < chessboard.grid.size(); i++) {
        GridCoppy[i] = chessboard.grid[i] ? chessboard.grid[i]->clone() : nullptr;
    }

    struct BestMove {
        float score = -1001;
        Vector2 from;
        Vector2 to;
    };
    BestMove bestMove;
    for (auto p : GridCoppy) {
        if (p && p->color == colorAI) {
            for (int i = 0; i < p->legalMoves.size(); i++) {
                Vector2 from = {p->position.x, p->position.y};
                float score = calculateMoveFaçade::get().CalculateMove(from, p->legalMoves[i], GridCoppy, colorAI);
                if (score > bestMove.score) {
                    bestMove.score = score;
                    bestMove.from = from;
                    bestMove.to = p->legalMoves[i];
                }
            }
        }
    }
    std::cout  << " best score move  " << bestMove.from.x << bestMove.from.y << " and total time " << GetTime() - startTime << std::endl;
    return new Move(bestMove.from, bestMove.to, chessboard);
}
