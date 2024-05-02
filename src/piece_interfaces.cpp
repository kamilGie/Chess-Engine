#include "piece_interfaces.hpp"

Piece::Piece(float column, float row, const std::string& pieceName) : position(Vector2{column, row}) {
    std::string fullPath = "Graphics/" + pieceName + ".png";
    Image image = LoadImage(fullPath.c_str());
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Piece::~Piece() { UnloadTexture(texture); }

void Piece::Draw() { DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE); }

bool Piece::isInBorder(int x, int y) { return x < 8 && y < 8 && x >= 0 && y >= 0; }

void Piece::addLegalMove(int x, int y) { legalMoves.push_back({static_cast<float>(x), static_cast<float>(y)}); }

void LongRangePiece::SetLegalMoves(Piece* grid[][8]) {
    legalMoves.clear();

    for (Vector2 dir : moveDirections) {
        for (int x = position.x + dir.x, y = position.y + dir.y; isInBorder(x, y); x += dir.x, y += dir.y) {
            bool isEmptyOrOpponent = !grid[x][y] || grid[x][y]->whiteColor() != whiteColor();
            if (isEmptyOrOpponent) addLegalMove(x, y);
            if (grid[x][y]) break;
        }
    }
}

#include <iostream>
void LimitedRangePiece::SetLegalMoves(Piece* grid[][8]) {
    legalMoves.clear();
    std::cout << "start" << std::endl;
    for (Vector2 dir : moveDirections) {
        int x = position.x + dir.x;
        int y = position.y + dir.y;
        bool isEmptyOrOpponent = isInBorder(x, y) && (!grid[x][y] || grid[x][y]->whiteColor() != whiteColor());
        if (isEmptyOrOpponent) addLegalMove(x, y);
    }
}
