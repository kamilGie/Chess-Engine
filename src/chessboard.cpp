#include "chessboard.hpp"
#include "pieces.hpp"

Chessboard::Chessboard() {}

void Chessboard::initPieces() {
    for (int i = 0; i < 8; ++i) {
        grid[i][1] = Pawn::CreateBlack(i, 1);
        grid[i][6] = Pawn::CreateWhite(i, 6);
    }
    grid[0][0] = Rook::CreateBlack(0, 0);
    grid[1][0] = Horse::CreateBlack(1, 0);
    grid[2][0] = Bishop::CreateBlack(2, 0);
    grid[4][0] = Queen::CreateBlack(4, 0);
    grid[3][0] = King::CreateBlack(3, 0);
    grid[5][0] = Bishop::CreateBlack(5, 0);
    grid[6][0] = Horse::CreateBlack(6, 0);
    grid[7][0] = Rook::CreateBlack(7, 0);

    grid[0][7] = Rook::CreateWhite(0, 7);
    grid[1][7] = Horse::CreateWhite(1, 7);
    grid[2][7] = Bishop::CreateWhite(2, 7);
    grid[4][7] = Queen::CreateWhite(4, 7);
    grid[3][7] = King::CreateWhite(3, 7);
    grid[5][7] = Bishop::CreateWhite(5, 7);
    grid[6][7] = Horse::CreateWhite(6, 7);
    grid[7][7] = Rook::CreateWhite(7, 7);
}

void Chessboard::DrawSquares() {
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

void Chessboard::DrawSelectedPieceDetails(std::shared_ptr<Piece> piece) {
        int x = piece->position.x;
        int y = piece->position.y;
        DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, SetClickedColor(x, y));
        piece->Draw();
        DrawLegalMoves(piece);
}

void Chessboard::DrawLegalMoves(std::shared_ptr<Piece> piece) {
    for (auto move : piece->legalMoves) {
        float x = move.x * cellSize + cellSize / 2;
        float y = move.y * cellSize + cellSize / 2;
        if (grid[(int)move.x][(int)move.y]) {
            DrawRing({x, y}, 40, 50, 0, 360, 32, Fade(BLACK, 0.1f));
        } else {
            DrawCircle(x, y, 17, Fade(BLACK, 0.1f));
        }
    }
}

void Chessboard::DrawPieces() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j]) grid[i][j]->Draw();
        }
    }
}
