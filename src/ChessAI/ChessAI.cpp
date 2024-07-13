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
    for(auto p : chessboard.grid){
            if (p && p->color == colorAI) {
                for (auto& to : p->legalMoves) {
                    Vector2 from = {p->position.x, p->position.y};
                    float score = CalculateMove(from, to, chessboard.grid, colorAI);
                    if (score > bestMove.score) {
                        bestMove.score = score;
                        bestMove.from = from;
                        bestMove.to = to;
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

float ChessAI::CalculateMove(Vector2 from, Vector2 to, std::array<std::shared_ptr<Piece>,64> grid, PieceColor colorTurn, int depth) {
    totalMoves++;
    float score = 1.0/(Vector2Distance({4,4}, to)+1);
    if (grid[(int)from.x+from.y*8]->getValue()==1) score+=0.5;
    int x = to.x;
    int y = to.y;
    PieceColor enemyColor = (colorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
    std::shared_ptr<Piece> pieceCaptured = grid[x+y*8];
    if (pieceCaptured) {
        score += pieceCaptured->getValue();
    }
    if (depth == 1) return score;

    grid[x+y*8] = grid[(int)from.x+from.y*8];
    grid[(int)from.x+from.y*8] = nullptr;

    Move::SetMoves(grid, enemyColor);
    bool NoPossibleMoves = std::all_of(&grid[0], &grid[64], [colorTurn](auto p) { return !p || p->color == colorTurn ||  p->legalMoves.empty(); });
    if (NoPossibleMoves) score = 1000;

    float TheWortsScenario=0;
    if (!NoPossibleMoves) {
        for(auto p : grid)
                if (p && p->color != colorTurn) {
                    for (auto& to : p->legalMoves) {
                        float EnemyMoveScore = CalculateMove({p->position.x, p->position.y }, to, grid, enemyColor, depth + 1);
                        if(EnemyMoveScore>TheWortsScenario) TheWortsScenario=EnemyMoveScore;
                    }
                }
            
        }
    
    score-=TheWortsScenario;

    grid[(int)from.x+from.y*8] = grid[x+y*8];
    grid[x+y*8] = pieceCaptured;
    return score;
}
