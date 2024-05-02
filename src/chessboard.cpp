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

    DrawRectangle(lastMovePositions[0].x * cellSize, lastMovePositions[0].y * cellSize, cellSize, cellSize, SetClickedColor(lastMovePositions[0].x, lastMovePositions[0].y));
    DrawRectangle(lastMovePositions[1].x * cellSize, lastMovePositions[1].y * cellSize, cellSize, cellSize, SetClickedColor(lastMovePositions[1].x, lastMovePositions[1].y));
}

void Chessboard::ShowSquares() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << (grid[j][i] ? grid[j][i]->getValue() : 0) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
