#include "piece.hpp"
#include "../factory/piece_factory.hpp"
#include "../models/king/king.hpp"

Piece::Piece(const float column, const float row, const std::string& pieceName, const PieceColor color) : position(Vector2{column, row}), color(color) {
    const std::string fullPath = "../Graphics/" + pieceName + ".png";
    const Image image = LoadImage(fullPath.c_str());
    texture = LoadTextureFromImage(image);
    PieceFactory::Get().addTexture(&texture);
    UnloadImage(image);
}

void Piece::Draw() const { DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE); }

PieceFactory& Piece::Create() { return PieceFactory::Get(); }

bool Piece::isInsideBoard(int x, int y) { return x < 8 && y < 8 && x >= 0 && y >= 0; }

void Piece::addLegalMove(int x, int y) { legalMoves.push_back({static_cast<float>(x), static_cast<float>(y)}); }

bool Piece::SafeMove(int x, int y, std::array<std::shared_ptr<Piece>,64> grid) {
    std::shared_ptr<Piece> tempCaptured = grid[x+y*8];
    grid[x+y*8] = std::move(grid[(int)position.x+position.y*8]);
    Vector2 BeforeMove = position;
    grid[(int)position.x+position.y*8] = nullptr;
    position = {static_cast<float>(x), static_cast<float>(y)};

    bool safe = !isKingChecked(grid);
    // Restore the original position of the moved piece
    position = BeforeMove;
    grid[(int)BeforeMove.x+BeforeMove.y*8] = std::move(grid[x+y*8]);
    grid[x+y*8] = tempCaptured;

    return safe;
}



bool Piece::isKingChecked(std::array<std::shared_ptr<Piece>,64> grid) {
    for (auto p : grid){
            if (p && p->color == color && p->getValue()==100) {
                if (std::static_pointer_cast<King>(p)->isGettingAtack(grid)) return true;
                else return false;
            }
    }
    return false;
}