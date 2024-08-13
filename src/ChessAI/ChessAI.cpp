#include "ChessAI.hpp"

#include <unordered_map>

#include "raymath.h"
#include "../chessboard/chessboard.hpp"
#include "../move/move.hpp"
#include "../pieces/bases/piece.hpp"
#include "Façade/calculateMoveFaçade.hpp"
#include "proxy/BestMove.hpp"
#include "../pieces/models/king/king.hpp"

ChessAI::ChessAI(PieceColor colorAI) : colorAI(colorAI) {}

ChessAI::~ChessAI() =default;

Move* ChessAI::GetMove(Chessboard& chessboard)  {
    std::array<std::shared_ptr<Piece>, 64> GridCoppy;
    for (int i = 0; i < chessboard.grid.size(); i++) {
        GridCoppy[i] = chessboard.grid[i] ? chessboard.grid[i]->clone() : nullptr;
    }

    Max_BestMove max_bestMove;
    for (const auto &p : GridCoppy) {
        if (p && p->color == colorAI) {
            for (int i = 0; i < p->legalMoves.size(); i++) {
                const Vector2 from = {p->position.x, p->position.y};
                const float score = CalculateMove(from, p->legalMoves[i], GridCoppy, colorAI);
                max_bestMove = {score, from, p->legalMoves[i]};  // assing if the score is better
            }
        }
    }
    return new Move(max_bestMove.value.from, max_bestMove.value.to, chessboard);
}

float ChessAI::CalculateMove(const Vector2 from, const Vector2 to, std::array<std::shared_ptr<Piece>, 64> grid, PieceColor colorTurn, const int depth) {
    float score = 1.0 / (Vector2Distance({3, 3}, to) + 1);
    const int indexTo = static_cast<int>(to.x) + to.y * 8;
    const int indexFrom = static_cast<int>(from.x) + from.y * 8;

    const PieceColor enemyColor = (colorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
    std::shared_ptr<Piece> pieceCaptured = std::move(grid[indexTo]);
    if (pieceCaptured) score += static_cast<float>(pieceCaptured->getValue());
    if (depth == 2) return score;

    std::unordered_map<int, std::vector<Vector2>> legalMovesMap;
    for (int i = 0; i < grid.size(); i++) {
        if (grid[i] && grid[i]->color == enemyColor) {
            legalMovesMap[i] = std::move(grid[i]->legalMoves);
        }
    }

    grid[indexTo] = std::move(grid[indexFrom]);
    grid[indexTo]->position = to;

    Move::SetMoves(grid, enemyColor);

    if (bool NoPossibleMoves = std::all_of(&grid[0], &grid[64], [colorTurn](auto p) { return !p || p->color == colorTurn || p->legalMoves.empty(); })) {
        for (const auto &p : grid) {
            if (p && p->color == enemyColor && p->getValue() == 100) {
                if (std::static_pointer_cast<King>(p)->isGettingAtack(grid)) score += 1000;
                break;
            }
        }
    } else {
        float TheWortsScenario = -1000;
        for (int i = 0; i < grid.size(); i++) {
            auto p = grid[i];
            if (p && p->color == enemyColor) {
                for (auto& to : p->legalMoves) {
                    int x = i % 8;
                    int y = i / 8;
                    Vector2 from = {float(x), float(y)};
                    float EnemyMoveScore = CalculateMove(from, to, grid, enemyColor, depth + 1);
                    if (EnemyMoveScore > TheWortsScenario) TheWortsScenario = EnemyMoveScore;
                }
            }
        }
        score -= TheWortsScenario;
    }

    grid[indexFrom] = std::move(grid[indexTo]);
    grid[indexFrom]->position = from;
    grid[indexTo] = std::move(pieceCaptured);

    for (auto& [index, legalMoves] : legalMovesMap) {
        grid[index]->legalMoves = std::move(legalMoves);
    }

    return score;
}
