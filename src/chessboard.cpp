#include "chessboard.hpp"

Chessboard::Chessboard() {}

void Chessboard::Draw() {
    DrawRectangle(0, 0, cellSize * cellCount, cellSize * cellCount, Green);

    for (int row = 0; row < cellCount; row++) {
        for (int column = 0; column < cellCount; column++) {
            if ((row + column) % 2) {
                DrawRectangle(row * cellSize, column * cellSize, cellSize, cellSize, White);
            }
        }
    }
}

void Chessboard::ShowSquares() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << (grid[i][j] ? grid[i][j]->getValue() : 0) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
