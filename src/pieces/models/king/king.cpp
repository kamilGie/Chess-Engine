#include "king.hpp"

void King::SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]) {
    LimitedRangePiece::SetLegalMoves(grid);
    // Castling
    if (moveCount == 0) {
        if (color == PieceColor::white) {
            if (grid[0][7] && grid[0][7]->moveCount == 0 && !grid[1][7] && !grid[2][7] && !isKingChecked(grid) && SafeMove(1, 7, grid) && SafeMove(2, 7, grid)) addLegalMove(1, 7);
            if (grid[7][7] && grid[7][7]->moveCount == 0 && !grid[6][7] && !grid[5][7] && !grid[4][7] && !isKingChecked(grid) && SafeMove(4, 7, grid) && SafeMove(5, 7, grid) && SafeMove(6, 7, grid)) addLegalMove(5, 7);
        } else {
            if (grid[0][0] && grid[0][0]->moveCount == 0 && !grid[1][0] && !grid[2][0] && !isKingChecked(grid) && SafeMove(2, 0, grid) && SafeMove(1, 0, grid)) addLegalMove(1, 0);
            if (grid[7][0] && grid[7][0]->moveCount == 0 && !grid[6][0] && !grid[5][0] && !grid[4][0] && !isKingChecked(grid) && SafeMove(4, 0, grid) && SafeMove(5, 0, grid) && SafeMove(6, 0, grid)) addLegalMove(5, 0);
        }
    }
}