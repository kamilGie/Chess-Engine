#include "piece_interfaces.hpp"

Piece::Piece(float column, float row, const std::string& pieceName) : position(Vector2{column, row}) {
    std::string fullPath = "Graphics/" + pieceName + ".png";
    Image image = LoadImage(fullPath.c_str());
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Piece::~Piece() { UnloadTexture(texture); }

void Piece::Draw() { DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE); }

bool Piece::isInsideBoard(int x, int y) { return x < 8 && y < 8 && x >= 0 && y >= 0; }

void Piece::addLegalMove(int x, int y) { legalMoves.push_back({static_cast<float>(x), static_cast<float>(y)}); }

void LongRangePiece::SetLegalMoves(std::shared_ptr<Piece> grid[][8]) {
    legalMoves.clear();

    for (Vector2 dir : moveDirections) {
        int x = position.x;
        int y = position.y;
        do {
            x += dir.x;
            y += dir.y;
            bool isEmptyOrOpponent = isInsideBoard(x, y) && (!grid[x][y] || grid[x][y]->color != color);
            if (isEmptyOrOpponent) addLegalMove(x, y);
        } while (!grid[x][y]);
    }
}

#include <iostream>
void LimitedRangePiece::SetLegalMoves(std::shared_ptr<Piece> grid[][8]) {
    legalMoves.clear();
    std::cout << "start" << std::endl;
    for (Vector2 dir : moveDirections) {
        int x = position.x + dir.x;
        int y = position.y + dir.y;
        bool isEmptyOrOpponent = isInsideBoard(x, y) && (!grid[x][y] || grid[x][y]->color != color);
        if (isEmptyOrOpponent) addLegalMove(x, y);
    }
}
