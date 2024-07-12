#include "ChessAI.hpp"

#include <iostream>
#include <raymath.h>
#include <memory>

#include "../chessboard/chessboard.hpp"
#include "../move/move.hpp"
#include "../pieces/bases/piece.hpp"

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
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessboard.grid[i][j] && chessboard.grid[i][j]->color == colorAI) {
                for (auto& to : chessboard.grid[i][j]->legalMoves) {
                    Vector2 from = {static_cast<float>(i), static_cast<float>(j)};
                    float score = CalculateMove(from, to, chessboard.grid, colorAI);
                    if (score > bestMove.score) {
                        bestMove.score = score;
                        bestMove.from = from;
                        bestMove.to = to;
                    }
                }
            }
        }
    }
    std::cout << "Total moves:  " << totalMoves << "and best score "<<bestMove.score<<std::endl
              << std::endl
              << std::endl;
    PieceColor enemyColor = (colorAI == PieceColor::white) ? PieceColor::black : PieceColor::white;
    Move::SetMoves(chessboard.grid, enemyColor);

    return new Move(bestMove.from, bestMove.to, chessboard);
}

float ChessAI::CalculateMove(Vector2 from, Vector2 to, std::shared_ptr<Piece> (&grid)[8][8], PieceColor colorTurn, int depth) {
    totalMoves++;
    float score = 1.0/(Vector2Distance({4,4}, to)+1);
    if (grid[(int)from.x][(int)from.y]->getValue()==1) score+=0.5;
    int x = to.x;
    int y = to.y;
    PieceColor enemyColor = (colorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
    std::shared_ptr<Piece> pieceCaptured = grid[x][y];
    if (pieceCaptured) {
        score += pieceCaptured->getValue();
    }
    if (depth == 1) return score;

    grid[x][y] = grid[(int)from.x][(int)from.y];
    grid[(int)from.x][(int)from.y] = nullptr;

    Move::SetMoves(grid, enemyColor);
    bool NoPossibleMoves = std::all_of(&grid[0][0], &grid[0][0] + 8 * 8, [&](auto& p) { return !p || p->color == colorTurn || p->legalMoves.empty(); });
    if (NoPossibleMoves) score = 1000;

    float TheWortsScenario=0;
    if (!NoPossibleMoves) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (grid[i][j] && grid[i][j]->color != colorTurn) {
                    for (auto& to : grid[i][j]->legalMoves) {
                        float EnemyMoveScore = CalculateMove({static_cast<float>(i), static_cast<float>(j)}, to, grid, enemyColor, depth + 1);
                        if(EnemyMoveScore>TheWortsScenario) TheWortsScenario=EnemyMoveScore;
                    }
                }
            }
        }
    }
    score-=TheWortsScenario;

    grid[(int)from.x][(int)from.y] = grid[x][y];
    grid[x][y] = pieceCaptured;
    return score;
}
