#include "pawn.hpp"

Pawn::Pawn(float column, float row, const std::string& pieceName, PieceColor color) : Piece(column, row, pieceName, color){};

void Pawn::SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]){
    legalMoves.clear();

    if (position.y == 7 || position.y == 0) return;
    int moveDirection = color == PieceColor::white ? -1 : 1;
    int x = position.x;
    int y = position.y + moveDirection;
    if (!grid[x][y]) {
        if (SafeMove(x, y, grid)) addLegalMove(x, y);
        if (moveCount == 0 && !grid[x][y + moveDirection] && SafeMove(x, y + moveDirection, grid)) addLegalMove(x, y + moveDirection);
    }
    if (x > 0 && grid[x - 1][y] && grid[x - 1][y]->color != color && SafeMove(x - 1, y, grid)) addLegalMove(x - 1, y);
    if (x < 7 && grid[x + 1][y] && grid[x + 1][y]->color != color && SafeMove(x + 1, y, grid)) addLegalMove(x + 1, y);
    if (en_passant.y > 0 && SafeMove(en_passant.x, en_passant.y, grid)) addLegalMove(en_passant.x, en_passant.y);
    en_passant = {0, 0};
}

bool Pawn::isAtackingKing(std::shared_ptr<Piece> grid[][8]) {
    int moveDirection = color == PieceColor::white ? -1 : 1;
    int x = position.x;
    int y = position.y + moveDirection;
    if (isInsideBoard(x - 1, y) && grid[x - 1][y] && grid[x - 1][y]->color != color && grid[x - 1][y]->getValue() == 100) return true;
    if (isInsideBoard(x + 1, y) && grid[x + 1][y] && grid[x + 1][y]->color != color && grid[x + 1][y]->getValue() == 100) return true;
    return false;
}