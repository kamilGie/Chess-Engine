#include "pieces.hpp"

#define ORTHOGONAL_MOVES \
    {1, 0}, {0, 1}, {-1, 0}, { 0, -1 }
#define DIAGONALLY_MOVES \
    {1, 1}, {1, -1}, {-1, 1}, { -1, -1 }
#define L_SHAPED_MOVES \
    {1, 2}, {2, 1}, {-2, 1}, {1, -2}, {-1, 2}, {2, -1}, {-1, -2}, { -2, -1 }

void King::SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]) {
    LimitedRangePiece::SetLegalMoves(grid);
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

King::King(float column, float row, const std::string& pieceName, PieceColor color) : LimitedRangePiece(column, row, pieceName, {ORTHOGONAL_MOVES, DIAGONALLY_MOVES}, color){};

Queen::Queen(float column, float row, const std::string& pieceName, PieceColor color) : LongRangePiece(column, row, pieceName, {{ORTHOGONAL_MOVES, DIAGONALLY_MOVES}}, color){};

Rook::Rook(float column, float row, const std::string& pieceName, PieceColor color) : LongRangePiece(column, row, pieceName, {ORTHOGONAL_MOVES}, color){};

Horse::Horse(float column, float row, const std::string& pieceName, PieceColor color) : LimitedRangePiece(column, row, pieceName, {L_SHAPED_MOVES}, color){};

Bishop::Bishop(float column, float row, const std::string& pieceName, PieceColor color) : LongRangePiece(column, row, pieceName, {DIAGONALLY_MOVES}, color){};

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

bool Pawn::SetAtackedPools(std::shared_ptr<Piece> grid[][8], bool atackedPools[8][8]) {
    int moveDirection = color == PieceColor::white ? -1 : 1;
    int x = position.x;
    int y = position.y + moveDirection;
    if (x > 0 && isInsideBoard(x - 1, y)) {
        atackedPools[x - 1][y] = true;
        if (grid[x - 1][y] && grid[x - 1][y]->color != color && grid[x - 1][y]->getValue() == 20) return true;
    }
    if (x < 7 && isInsideBoard(x + 1, y)) {
        atackedPools[x + 1][y] = true;
        if (grid[x + 1][y] && grid[x + 1][y]->color != color && grid[x + 1][y]->getValue() == 20) return true;
    }
    return false;
}