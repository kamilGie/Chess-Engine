#include "ChessAI.hpp"

#include <raymath.h>

#include <memory>
#include <unordered_map>

#include "../chessboard/chessboard.hpp"
#include "../move/move.hpp"
#include "../pieces/bases/piece.hpp"
#include "../pieces/models/king/king.hpp"
#include "proxy/BestMove.hpp"

#include "Façade/calculateMoveFaçade.hpp"

ChessAI::ChessAI(PieceColor colorAI) : colorAI(colorAI) {}

ChessAI::~ChessAI() {}

Move* ChessAI::GetMove(Chessboard& chessboard) {
    double startTime = GetTime();
    std::array<std::shared_ptr<Piece>, 64> GridCoppy;
    for (int i = 0; i < chessboard.grid.size(); i++) {
        GridCoppy[i] = chessboard.grid[i] ? chessboard.grid[i]->clone() : nullptr;
    }


    Max_BestMove max_bestMove;
    for (auto p : GridCoppy) {
        if (p && p->color == colorAI) {
            for (int i = 0; i < p->legalMoves.size(); i++) {
                Vector2 from = {p->position.x, p->position.y};
                float score = calculateMoveFaçade::get().CalculateMove(from, p->legalMoves[i], GridCoppy, colorAI);
                max_bestMove = {score, from, p->legalMoves[i]};// assing if the score is better
            }
        }
    }
    return new Move(max_bestMove.value.from, max_bestMove.value.to, chessboard);
}
