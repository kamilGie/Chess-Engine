#include "ChessAI.hpp"
#include "../chessboard/chessboard.hpp"
#include "../move/move.hpp"
#include "../pieces/bases/piece.hpp"



ChessAI::ChessAI(PieceColor colorAI):colorAI(colorAI) { }

ChessAI::~ChessAI() {
}

Move* ChessAI::GetMove(Chessboard& chessboard) {
    struct BestMove {
        float score=-1;
        Vector2 from;
        Vector2 to;
    };
    BestMove bestMove;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessboard.grid[i][j] && chessboard.grid[i][j]->color == colorAI) {
                for (auto& [x,y] : chessboard.grid[i][j]->legalMoves) {

                        if(bestMove.score==-1 || (chessboard.grid[(int)x][(int)y] && chessboard.grid[(int)x][(int)y]->color!=colorAI && bestMove.score < chessboard.grid[(int)x][(int)y]->getValue())){
                            bestMove.score= chessboard.grid[int(x)][int(y)] ? chessboard.grid[int(x)][int(y)]->getValue() : 0; 
                            bestMove.from={(float)i,(float)j};
                            bestMove.to={x,y};
                        }
                }
            }
        }
    }
    return new Move(bestMove.from,bestMove.to,chessboard);
}