#include "piece_longRange.hpp"

void LongRangePiece::SetMoves(std::array<std::shared_ptr<Piece>,64> grid) {
    legalMoves.clear();

    for (Vector2 dir : moveDirections) {
        int x = position.x;
        int y = position.y;
        do {
            x += dir.x;
            y += dir.y;
            bool isEmptyOrOpponent = isInsideBoard(x, y) && (!grid[x+y*8] || grid[x+y*8]->color != color);
            if (isEmptyOrOpponent) addLegalMove(x, y);
        } while (!grid[x+y*8]);
    }
}


bool LongRangePiece::isAtackingKing(std::array<std::shared_ptr<Piece>,64> grid) {
    for (Vector2 dir : moveDirections) {
        int x = position.x;
        int y = position.y;
        do {
            x += dir.x;
            y += dir.y;
            if (isInsideBoard(x, y) && grid[x+y*8] && grid[x+y*8]->getValue() == 100 &&  grid[x+y*8]->color != color)  return true;
        } while (!grid[x+y*8]);
    }
    return false;
}