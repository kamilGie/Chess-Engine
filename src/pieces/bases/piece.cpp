#include "piece.hpp"
#include "../factory/piece_factory.hpp"

Piece::Piece(float column, float row, const std::string& pieceName, PieceColor color) : position(Vector2{column, row}), color(color) {
    std::string fullPath = "../Graphics/" + pieceName + ".png";
    Image image = LoadImage(fullPath.c_str());
    texture = LoadTextureFromImage(image);
    PieceFactory::Get().addTexture(&texture);
    UnloadImage(image);
}

void Piece::Draw() { DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE); }

PieceFactory& Piece::Create() { return PieceFactory::Get(); }

bool Piece::isInsideBoard(int x, int y) { return x < 8 && y < 8 && x >= 0 && y >= 0; }

void Piece::addLegalMove(int x, int y) { legalMoves.push_back({static_cast<float>(x), static_cast<float>(y)}); }

bool Piece::SafeMove(int x, int y, std::shared_ptr<Piece> grid[][8]) {
    std::shared_ptr<Piece> tempCaptured = grid[x][y];
    grid[x][y] = std::move(grid[(int)position.x][(int)position.y]);
    Vector2 BeforeMove = position;
    grid[(int)position.x][(int)position.y] = nullptr;
    position = {static_cast<float>(x), static_cast<float>(y)};

    bool safe = !isKingChecked(grid);

    // Restore the original position of the moved piece
    position = BeforeMove;
    grid[(int)BeforeMove.x][(int)BeforeMove.y] = std::move(grid[x][y]);
    grid[x][y] = tempCaptured;

    return safe;
}

bool Piece::isKingChecked(std::shared_ptr<Piece> grid[][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] && grid[i][j]->color != color && grid[i][j]->isAtackingKing(grid)) return true;
        }
    }
    return false;
}