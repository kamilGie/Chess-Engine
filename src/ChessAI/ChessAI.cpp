#include "ChessAI.hpp"

#include <raymath.h>

#include <iostream>
#include <memory>

#include "../chessboard/chessboard.hpp"
#include "../move/move.hpp"
#include "../pieces/bases/piece.hpp"
#include "../pieces/models/king/king.hpp"

ChessAI::ChessAI(PieceColor colorAI) : colorAI(colorAI) {}

ChessAI::~ChessAI() {
}
int totalMoves = 0;

Move* ChessAI::GetMove(Chessboard& chessboard) {
    struct BestMove {
        float score = -1001;
        Vector2 from;
        Vector2 to;
    };
    totalMoves = 0;
    BestMove bestMove;
    for (auto p : chessboard.grid) {
        if (p && p->color == colorAI) {
            for (int i = 0; i < p->legalMoves.size(); i++) {
                Vector2 from = {p->position.x, p->position.y};
                float score = CalculateMove(from, p->legalMoves[i], chessboard.grid, colorAI);
                if (score > bestMove.score) {
                    bestMove.score = score;
                    bestMove.from = from;
                    bestMove.to = p->legalMoves[i];
                }
            }
        }
    }
    std::cout << "Total moves:  " << totalMoves << "and best score move  " << bestMove.from.x << bestMove.from.y << std::endl;

    return new Move(bestMove.from, bestMove.to, chessboard);
}

float ChessAI::CalculateMove(Vector2 from, Vector2 to, std::array<std::shared_ptr<Piece>, 64> grid, PieceColor colorTurn, int depth) {
    if(GetRandomValue(0,8) ==2 ) return 0;
    totalMoves++;
    float score = 1.0 / (Vector2Distance({(float)GetRandomValue(2,5), (float)GetRandomValue(2,5)}, to) + 1);
    int x = static_cast<int>(to.x);
    int y = static_cast<int>(to.y);

    PieceColor enemyColor = (colorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
    std::shared_ptr<Piece> pieceCaptured = grid[x + y * 8];
    if (pieceCaptured) score += pieceCaptured->getValue();
    if (depth == 2) return score;

    grid[x + y * 8] = grid[(int)from.x + from.y * 8];
    grid[x + y * 8]->position = to;
    grid[(int)from.x + from.y * 8] = nullptr;

    Move::SetMoves(grid, enemyColor);
    bool NoPossibleMoves = std::all_of(&grid[0], &grid[64], [colorTurn](auto p) { return !p || p->color == colorTurn || p->legalMoves.empty(); });

    if (NoPossibleMoves) {
        for (auto p : grid) {
            if (p && p->color == enemyColor && p->getValue() == 100) {
                if (std::static_pointer_cast<King>(p)->isGettingAtack(grid)) score += 1000;
                break;
            }
        }
    }

    if (!NoPossibleMoves) {
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

    grid[(int)from.x + from.y * 8] = grid[x + y * 8];
    grid[(int)from.x + from.y * 8]->position = from;
    grid[x + y * 8] = pieceCaptured;
    Move::SetMoves(grid, colorTurn);
    return score;
}
