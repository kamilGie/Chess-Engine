#include "calculateMoveFaçade.hpp"

#include <raymath.h>

#include <unordered_map>

#include "../../chessboard/chessboard.hpp"
#include "../../move/move.hpp"
#include "../../pieces/bases/piece.hpp"
#include "../../pieces/models/king/king.hpp"

calculateMoveFaçade& calculateMoveFaçade::get() {
    static calculateMoveFaçade instance;
    return instance;
}

float calculateMoveFaçade::CalculateMove(Vector2 from, Vector2 to, std::array<std::shared_ptr<Piece>, 64> grid, PieceColor colorTurn, int depth) {
    float score = 1.0 / (Vector2Distance({3, 3}, to) + 1);
    int indexTo = to.x + to.y * 8;
    int indexFrom = from.x + from.y * 8;

    PieceColor enemyColor = (colorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
    std::shared_ptr<Piece> pieceCaptured = std::move(grid[indexTo]);
    if (pieceCaptured) score += pieceCaptured->getValue();
    if (depth == 3) return score;

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
        for (auto p : grid) {
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