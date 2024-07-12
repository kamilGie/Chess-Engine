#include "piece_longRange.hpp"

void LongRangePiece::SetMoves(std::shared_ptr<Piece> (&grid)[][8]) {
    legalMoves.clear();

    for (Vector2 dir : moveDirections) {
        int x = position.x;
        int y = position.y;
        do {
            x += dir.x;
            y += dir.y;
            bool isEmptyOrOpponent = isInsideBoard(x, y) && (!grid[x][y] || grid[x][y]->color != color);
            if (isEmptyOrOpponent) addLegalMove(x, y);
        } while (!grid[x][y]);
    }
}


bool LongRangePiece::isAtackingKing(std::shared_ptr<Piece> grid[][8]) {
    for (Vector2 dir : moveDirections) {
        int x = position.x;
        int y = position.y;
        do {
            x += dir.x;
            y += dir.y;
            if (isInsideBoard(x, y) && grid[x][y] && grid[x][y]->color != color && grid[x][y]->getValue() == 100)  return true;
        } while (!grid[x][y]);
    }
    return false;
}