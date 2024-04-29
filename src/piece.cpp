#include "piece.hpp"

Piece::Piece(float column, float row, const std::string& pieceName) : position(Vector2{row, column}) {
    std::string fullPath = "Graphics/" + pieceName + ".png";
    Image image = LoadImage(fullPath.c_str());
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Piece::~Piece() { UnloadTexture(texture); }

void Piece::Draw() { DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE); }
