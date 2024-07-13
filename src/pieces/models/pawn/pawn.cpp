#include "pawn.hpp"
#include <iostream>

Pawn::Pawn(float column, float row, const std::string& pieceName, PieceColor color) : Piece(column, row, pieceName, color){};

void Pawn::SetMoves(std::array<std::shared_ptr<Piece>,64> grid){
    legalMoves.clear();

    if (position.y == 7 || position.y == 0) return;
    int moveDirection = color == PieceColor::white ? -1 : 1;
    int x = position.x;
    int y = position.y + moveDirection;
    if (!grid[x+y*8]) {
        addLegalMove(x, y);
        if (moveCount == 0 && !grid[x + (y + moveDirection)*8]) addLegalMove(x, y + moveDirection);
    }
    int left =  x-1+y*8;
    if (x > 0 && grid[left] && grid[left]->color != color) addLegalMove(x - 1, y);
    int right = x+1+y*8;
    if (x < 7 && grid[right] && grid[right]->color != color) addLegalMove(x + 1, y);
    if (en_passant.y > 0) addLegalMove(en_passant.x, en_passant.y);
    en_passant = {0, 0};
}

bool Pawn::isAtackingKing(std::array<std::shared_ptr<Piece>,64> grid) {
    int moveDirection = color == PieceColor::white ? -1 : 1;
    int x = position.x;
    int y = position.y + moveDirection;

    int left =  x-1+y*8;
    if (isInsideBoard(x - 1, y) && grid[left] && grid[left]->color != color && grid[left]->getValue() == 100) return true;

    int right = x+1+y*8;
    if (isInsideBoard(x + 1, y) && grid[right] && grid[right]->color != color && grid[right]->getValue() == 100) return true;
    return false;
}