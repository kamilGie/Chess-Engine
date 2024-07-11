#include "piece_limitedRange.hpp"

bool LimitedRangePiece::isAtackingKing(std::shared_ptr<Piece> grid[][8]) {
    for (Vector2 dir : moveDirections) {
        int x = position.x + dir.x;
        int y = position.y + dir.y;
        if (isInsideBoard(x, y)) {
            if (grid[x][y] && grid[x][y]->color != color && grid[x][y]->getValue() == 100) return true;
        }
    }
    return false;
}

void LimitedRangePiece::SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]) {
    legalMoves.clear();
    for (Vector2 dir : moveDirections) {
        int x = position.x + dir.x;
        int y = position.y + dir.y;
        bool isEmptyOrOpponent = isInsideBoard(x, y) && (!grid[x][y] || grid[x][y]->color != color);
        if (isEmptyOrOpponent && SafeMove(x, y, grid)) addLegalMove(x, y);
    }
}