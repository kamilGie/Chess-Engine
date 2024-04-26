#include "chessboard.hpp"
#include <raylib.h>

Chessboard::Chessboard() {}

void Chessboard::Draw() {
    DrawRectangle(0, 0, cellSize * cellCount, cellSize * cellCount, BEIGE);

    for (int row = 0; row < cellCount; row++) {
        for (int column = 0; column < cellCount; column++) {
            if ((row+column)%2) {
                DrawRectangle(row * cellSize, column * cellSize, cellSize, cellSize, DARKBROWN);
            }
        }
    }
}
