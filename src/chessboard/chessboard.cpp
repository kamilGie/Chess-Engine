#include "chessboard.hpp"
#include "../resources/colors.hpp"
#include "../pieces/pieces.hpp"
#include "../pieces/piece_factory.hpp"

Chessboard::~Chessboard() {
    PieceFactory::UnloadTextures();
}

void Chessboard::initPieces() {
    for (int i = 0; i < 8; ++i) {
        grid[i][1] = Piece::Create().PawnBlack().Position(i,1);
        grid[i][6] = Piece::Create().PawnWhite().Position(i,6);
    }
    grid[0][0] = Piece::Create().RookBlack().Position(0, 0);
    grid[1][0] = Piece::Create().HorseBlack().Position(1, 0);
    grid[2][0] = Piece::Create().BishopBlack().Position(2, 0);
    grid[4][0] = Piece::Create().QueenBlack().Position(4, 0);
    grid[3][0] = Piece::Create().KingBlack().Position(3, 0);
    grid[5][0] = Piece::Create().BishopBlack().Position(5, 0);
    grid[6][0] = Piece::Create().HorseBlack().Position(6, 0);
    grid[7][0] = Piece::Create().RookBlack().Position(7, 0);

    grid[0][7] = Piece::Create().RookWhite().Position(0, 7);
    grid[1][7] = Piece::Create().HorseWhite().Position(1, 7);
    grid[2][7] = Piece::Create().BishopWhite().Position(2, 7);
    grid[4][7] = Piece::Create().QueenWhite().Position(4, 7);
    grid[3][7] = Piece::Create().KingWhite().Position(3, 7);
    grid[5][7] = Piece::Create().BishopWhite().Position(5, 7);
    grid[6][7] = Piece::Create().HorseWhite().Position(6, 7);
    grid[7][7] = Piece::Create().RookWhite().Position(7, 7);
    
    // Set starting legal moves (pawn and horse)
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
