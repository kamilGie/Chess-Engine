#include "pieces.hpp"

#define ORTHOGONAL_MOVES \
    {1, 0}, {0, 1}, {-1, 0}, { 0, -1 }
#define DIAGONALLY_MOVES \
    {1, 1}, {1, -1}, {-1, 1}, { -1, -1 }
#define L_SHAPED_MOVES \
    {1, 2}, {2, 1}, {-2, 1}, {1, -2}, {-1, 2}, {2, -1}, {-1, -2}, { -2, -1 }

void King::SetLegalMoves(std::shared_ptr<Piece> grid[][8]) {
    LimitedRangePiece::SetLegalMoves(grid);
    if (moveCount == 0) {
        if (color == PieceColor::white) {
            if (grid[0][7] && grid[0][7]->moveCount == 0 && !grid[1][7] && !grid[2][7] && SafeMove(3, 7, grid) && SafeMove(2, 7, grid)) addLegalMove(1, 7);
            if (grid[7][7] && grid[7][7]->moveCount == 0 && !grid[6][7] && !grid[5][7] && !grid[4][7] && SafeMove(4, 7, grid) && SafeMove(5, 7, grid) && SafeMove(6, 7, grid)) addLegalMove(5, 7);
        } else {
            if (grid[0][0] && grid[0][0]->moveCount == 0 && !grid[1][0] && !grid[2][0] && SafeMove(3, 0, grid) && SafeMove(2, 0, grid)) addLegalMove(1, 0);
            if (grid[7][0] && grid[7][0]->moveCount == 0 && !grid[6][0] && !grid[5][0] && !grid[4][0] && SafeMove(4, 0, grid) && SafeMove(5, 0, grid) && SafeMove(6, 0, grid)) addLegalMove(5, 0);
        }
    }
}
King::King(float column, float row, const std::string& pieceName, PieceColor color) : LimitedRangePiece(column, row, pieceName, {ORTHOGONAL_MOVES, DIAGONALLY_MOVES}, color){};
std::shared_ptr<King> King::CreateBlack(float column, float row) { return std::make_shared<King>(column, row, "kingBlack", PieceColor::black); }
std::shared_ptr<King> King::CreateWhite(float column, float row) { return std::make_shared<King>(column, row, "kingWhite", PieceColor::white); }

Queen::Queen(float column, float row, const std::string& pieceName, PieceColor color) : LongRangePiece(column, row, pieceName, {{ORTHOGONAL_MOVES, DIAGONALLY_MOVES}}, color){};
std::shared_ptr<Queen> Queen::CreateBlack(float column, float row) { return std::make_shared<Queen>(column, row, "QueenBlack", PieceColor::black); }
std::shared_ptr<Queen> Queen::CreateWhite(float column, float row) { return std::make_shared<Queen>(column, row, "QueenWhite", PieceColor::white); }

Rook::Rook(float column, float row, const std::string& pieceName, PieceColor color) : LongRangePiece(column, row, pieceName, {ORTHOGONAL_MOVES}, color){};
std::shared_ptr<Rook> Rook::CreateBlack(float column, float row) { return std::make_shared<Rook>(column, row, "RookBlack", PieceColor::black); }
std::shared_ptr<Rook> Rook::CreateWhite(float column, float row) { return std::make_shared<Rook>(column, row, "RookWhite", PieceColor::white); }

// ### HORSE ###//

Horse::Horse(float column, float row, const std::string& pieceName, PieceColor color) : LimitedRangePiece(column, row, pieceName, {L_SHAPED_MOVES}, color){};
std::shared_ptr<Horse> Horse::CreateBlack(float column, float row) { return std::make_shared<Horse>(column, row, "HorseBlack", PieceColor::black); }
std::shared_ptr<Horse> Horse::CreateWhite(float column, float row) { return std::make_shared<Horse>(column, row, "HorseWhite", PieceColor::white); }

Bishop::Bishop(float column, float row, const std::string& pieceName, PieceColor color) : LongRangePiece(column, row, pieceName, {DIAGONALLY_MOVES}, color){};
std::shared_ptr<Bishop> Bishop::CreateBlack(float column, float row) { return std::make_shared<Bishop>(column, row, "BishopBlack", PieceColor::black); }
std::shared_ptr<Bishop> Bishop::CreateWhite(float column, float row) { return std::make_shared<Bishop>(column, row, "BishopWhite", PieceColor::white); }

Pawn::Pawn(float column, float row, const std::string& pieceName, PieceColor color) : Piece(column, row, pieceName, color){};

void Pawn::SetLegalMoves(std::shared_ptr<Piece> grid[][8]){
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

std::shared_ptr<Pawn> Pawn::CreateBlack(float column, float row) { return std::make_shared<Pawn>(column, row, "pawnBlack", PieceColor::black); }
std::shared_ptr<Pawn> Pawn::CreateWhite(float column, float row) { return std::make_shared<Pawn>(column, row, "pawnWhite", PieceColor::white); }