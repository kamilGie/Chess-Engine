#include "chessboard.hpp"
#include "../resources/colors.hpp"
#include "../pieces/pieces.hpp"
#include "../pieces/piece_factory.hpp"
Chessboard::Chessboard() {}

Chessboard::~Chessboard() {
    PieceFactory::UnloadTextures();
}

void Chessboard::initPieces() {
    for (int i = 0; i < 8; ++i) {
        grid[i][1] = PieceFactory::BlackPawn(i,1);
        grid[i][6] = PieceFactory::WhitePawn(i,6);
    }
    grid[0][0] = PieceFactory::BlackRook(0, 0);
    grid[1][0] = PieceFactory::BlackHorse(1, 0);
    grid[2][0] = PieceFactory::BlackBishop(2, 0);
    grid[4][0] = PieceFactory::BlackQueen(4, 0);
    grid[3][0] = PieceFactory::BlackKing(3, 0);
    grid[5][0] = PieceFactory::BlackBishop(5, 0);
    grid[6][0] = PieceFactory::BlackHorse(6, 0);
    grid[7][0] = PieceFactory::BlackRook(7, 0);

    grid[0][7] = PieceFactory::WhiteRook(0, 7);
    grid[1][7] = PieceFactory::WhiteHorse(1, 7);
    grid[2][7] = PieceFactory::WhiteBishop(2, 7);
    grid[4][7] = PieceFactory::WhiteQueen(4, 7);
    grid[3][7] = PieceFactory::WhiteKing(3, 7);
    grid[5][7] = PieceFactory::WhiteBishop(5, 7);
    grid[6][7] = PieceFactory::WhiteHorse(6, 7);
    grid[7][7] = PieceFactory::WhiteRook(7, 7);
    
    // Set starting legal moves
    for (int i = 0; i < 8; ++i) {
        grid[i][1]->SetLegalMoves(grid);
        grid[i][6]->SetLegalMoves(grid);
    }
    grid[1][0]->SetLegalMoves(grid);
    grid[6][0]->SetLegalMoves(grid);
    grid[1][7]->SetLegalMoves(grid);
    grid[6][7]->SetLegalMoves(grid);

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

void Chessboard::SetLastMovePositions(Vector2 from, Vector2 to) {
    lastMovePositions[0] = from;
    lastMovePositions[1] = to;
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
