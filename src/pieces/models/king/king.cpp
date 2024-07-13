#include "king.hpp"
#include <iostream>

void King::SetMoves(std::array<std::shared_ptr<Piece>,64> grid) {
    LimitedRangePiece::SetMoves(grid);
    // Castling
    // if (moveCount == 0) { todo
    //     if (color == PieceColor::white) {
    //         if (grid[0][7] && grid[0][7]->moveCount == 0 && !grid[1][7] && !grid[2][7] && !isKingChecked(grid) && SafeMove(1, 7, grid) && SafeMove(2, 7, grid)) addLegalMove(1, 7);
    //         if (grid[7][7] && grid[7][7]->moveCount == 0 && !grid[6][7] && !grid[5][7] && !grid[4][7] && !isKingChecked(grid) && SafeMove(4, 7, grid) && SafeMove(5, 7, grid) && SafeMove(6, 7, grid)) addLegalMove(5, 7);
    //     } else {
    //         if (grid[0][0] && grid[0][0]->moveCount == 0 && !grid[1][0] && !grid[2][0] && !isKingChecked(grid) && SafeMove(2, 0, grid) && SafeMove(1, 0, grid)) addLegalMove(1, 0);
    //         if (grid[7][0] && grid[7][0]->moveCount == 0 && !grid[6][0] && !grid[5][0] && !grid[4][0] && !isKingChecked(grid) && SafeMove(4, 0, grid) && SafeMove(5, 0, grid) && SafeMove(6, 0, grid)) addLegalMove(5, 0);
    //     }
    // }
}

bool King::isGettingAtack(std::array<std::shared_ptr<Piece>,64> grid) {
    for (Vector2 dir : moveDirections) {
        int x = position.x;
        int y = position.y;
        std::shared_ptr<Piece> p;
        do {
            x += dir.x;
            y += dir.y;
            if (!isInsideBoard(x, y)) break;

            p = grid[x+y*8];
            if (p && p->color != color && p->isAtackingKing(grid)) return true;
            
        } while (!p);
    }

    for (auto& dir : std::vector<Vector2>{L_SHAPED_MOVES}) {
        int x = position.x + dir.x;
        int y = position.y + dir.y;
        if (isInsideBoard(x, y) && grid[x+y*8] && grid[x+y*8]->color != color && grid[x+y*8]->getValue() == 4) return true;
    }

    return false;
}

void King::SetLegalMoves(std::array<std::shared_ptr<Piece>,64> grid) {
    for (Vector2 dir : moveDirections) {
        int x = position.x;
        int y = position.y;
        std::shared_ptr<Piece> p;
        do {
            x += dir.x;
            y += dir.y;
            if (!isInsideBoard(x, y)) break;

            p = grid[x+y*8];
            if (p) {
                if (p->color == color) {
                    for (auto it = p->legalMoves.begin(); it != p->legalMoves.end();) {
                        if (!p->SafeMove(it->x, it->y, grid)) {
                            it = p->legalMoves.erase(it);
                        } else {
                            ++it;
                        }
                    }
                } else if (p->isAtackingKing(grid)) {
                    for(auto pc: grid){
                            if (pc && pc->color == color) {
                                for (auto it = pc->legalMoves.begin(); it != pc->legalMoves.end();) {
                                    if (!pc->SafeMove(it->x, it->y, grid)) {
                                        it = pc->legalMoves.erase(it);
                                    } else {
                                        it++;
                                    }
                                }
                            }
                        }
                    
                    return;
                }
            }

        } while (!p);
    }

    for (auto& dir : std::vector<Vector2>{L_SHAPED_MOVES}) {
        int x = position.x + dir.x;
        int y = position.y + dir.y;
        if (isInsideBoard(x, y) && grid[x+y*8] && grid[x+y*8]->color != color && grid[x+y*8]->getValue() == 4) {
            for(auto pc: grid){
                    if (pc && pc->color == color) {
                        for (auto it = pc->legalMoves.begin(); it != pc->legalMoves.end();) {
                            if (!pc->SafeMove(it->x, it->y, grid)) {
                                it = pc->legalMoves.erase(it);
                            } else {
                                ++it;
                            }
                        }
                    }
            }
            return;
        }
    }
    for(auto it = legalMoves.begin(); it != legalMoves.end();) {
        if (!SafeMove(it->x, it->y, grid)) {
            it = legalMoves.erase(it);
        } else {
            ++it;
        }
    }
}
