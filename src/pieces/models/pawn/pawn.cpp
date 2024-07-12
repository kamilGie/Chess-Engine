#include "pawn.hpp"
#include <iostream>

Pawn::Pawn(float column, float row, const std::string& pieceName, PieceColor color) : Piece(column, row, pieceName, color){};

void Pawn::SetMoves(std::shared_ptr<Piece> (&grid)[][8]){
    legalMoves.clear();

    if (position.y == 7 || position.y == 0) return;
    int moveDirection = color == PieceColor::white ? -1 : 1;
    int x = position.x;
    int y = position.y + moveDirection;
    if (!grid[x][y]) {
        addLegalMove(x, y);
        std::cout<<grid[x][y + moveDirection]<<std::endl;
        if (moveCount == 0 && !grid[x][y + moveDirection]) addLegalMove(x, y + moveDirection);
    }
    if (x > 0 && grid[x - 1][y] && grid[x - 1][y]->color != color) addLegalMove(x - 1, y);
    if (x < 7 && grid[x + 1][y] && grid[x + 1][y]->color != color) addLegalMove(x + 1, y);
    if (en_passant.y > 0) addLegalMove(en_passant.x, en_passant.y);
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