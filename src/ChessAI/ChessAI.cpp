#include "ChessAI.hpp"

#include <memory>
#include <iostream>

#include "../chessboard/chessboard.hpp"
#include "../move/move.hpp"
#include "../pieces/bases/piece.hpp"

ChessAI::ChessAI(PieceColor colorAI) : colorAI(colorAI) {}

ChessAI::~ChessAI() {
}
int totalMoves=0;

Move* ChessAI::GetMove(Chessboard& chessboard) {
    struct BestMove {
        float score = -1;
        Vector2 from;
        Vector2 to;
    };
    totalMoves=0;
    BestMove bestMove;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessboard.grid[i][j] && chessboard.grid[i][j]->color == colorAI) {
                for (auto& to : chessboard.grid[i][j]->legalMoves) {
                    Vector2 from = {static_cast<float>(i), static_cast<float>(j)};
                    float score = CalculateMove(from, to, chessboard.grid,colorAI);
                    if (score > bestMove.score) {
                        bestMove.score = score;
                        bestMove.from = from;
                        bestMove.to = to;
                    }
                }
            }
        }
    }
    std::cout<<"Total moves: "<<totalMoves<<std::endl<<std::endl<<std::endl;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (chessboard.grid[i][j] && chessboard.grid[i][j]->color != colorAI) {
                chessboard.grid[i][j]->SetLegalMoves(chessboard.grid);
            }
        }
    }

    return new Move(bestMove.from, bestMove.to, chessboard);
}

float ChessAI::CalculateMove(Vector2 from, Vector2 to, std::shared_ptr<Piece> (&grid)[8][8],PieceColor colorTurn,int depth) {
    totalMoves++;
    float score = 0;
    int x = to.x;
    int y = to.y;
    std::shared_ptr<Piece> pieceCaptured = grid[x][y];
    if (pieceCaptured) {
        score += pieceCaptured->getValue();
    }
    if (depth == 2) return score;

    grid[x][y] = grid[(int)from.x][(int)from.y];
    grid[(int)from.x][(int)from.y] = nullptr;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (grid[i][j] && grid[i][j]->color != colorTurn) {
                grid[i][j]->SetLegalMoves(grid);
            }
        }
    }


    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] && grid[i][j]->color != colorTurn) {
                for (auto& to : grid[i][j]->legalMoves) {
                    Vector2 from = {static_cast<float>(i), static_cast<float>(j)};
                    if (colorTurn == PieceColor::white) score -= CalculateMove(from, to, grid,PieceColor::black,depth+1);
                    else score -= CalculateMove(from, to, grid,PieceColor::white,depth+1);
                }
            }
        }
    }
    grid[(int)from.x][(int)from.y] = grid[x][y];
    grid[x][y] = pieceCaptured;
    return score;
}
