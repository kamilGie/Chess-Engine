#include "piece_interfaces.hpp"

#include <iostream>

Piece::Piece(float column, float row, const std::string& pieceName) : position(Vector2{column, row}) {
    std::string fullPath = "Graphics/" + pieceName + ".png";
    Image image = LoadImage(fullPath.c_str());
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Piece::~Piece() { UnloadTexture(texture); }

void Piece::Draw() { DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE); }

bool isInBorder(int x, int y) { return x < 8 && y < 8 && x >= 0 && y >= 0; }

void LongRangePiece::SetLegalMoves(Piece* grid[][8]) {
    legalMoves.clear();

    for (Vector2 dir : moveDirections) {
        for (int x = position.x + dir.x, y = position.y + dir.y; isInBorder(x, y); x += dir.x, y += dir.y) {
            bool isEmptyOrOpponent = !grid[x][y] || grid[x][y]->whiteColor() != whiteColor();
            if (isEmptyOrOpponent) legalMoves.push_back({(float)x, (float)y});
            if (grid[x][y]) break;
        }
    }
}

void LimitedRangePiece::SetLegalMoves(Piece* grid[][8]) {
    legalMoves.clear();

    for (Vector2 dir : moveDirections) {
        int x = position.x + dir.x;
        int y = position.y + dir.y;
        bool isEmptyOrOpponent = !grid[x][y] || grid[x][y]->whiteColor() != whiteColor();
        if (isInBorder(x, y) && isEmptyOrOpponent )  legalMoves.push_back({(float)x, (float)y});
    }
}
