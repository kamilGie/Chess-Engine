#include "piece_limitedRange.hpp"

bool LimitedRangePiece::isAtackingKing(std::array<std::shared_ptr<Piece>,64> grid) {
    for (Vector2 dir : moveDirections) {
        int x = position.x + dir.x;
        int y = position.y + dir.y;
        if (isInsideBoard(x, y) && grid[x+y*8] && grid[x+y*8]->color != color && grid[x+y*8]->getValue() == 100) return true;
    }
    return false;
}

void LimitedRangePiece::SetMoves(std::array<std::shared_ptr<Piece>,64> grid) {
    legalMoves.clear();
    for (Vector2 dir : moveDirections) {
        int x = position.x + dir.x;
        int y = position.y + dir.y;
        const bool isEmptyOrOpponent = isInsideBoard(x, y) && (!grid[x+y*8] || grid[x+y*8]->color != color);
        if (isEmptyOrOpponent) addLegalMove(x, y);
    }
}