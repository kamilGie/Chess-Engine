#include "chessboard.hpp"
#include "../resources/colors.hpp"
#include "../pieces/models/include.hpp"
#include "../pieces/factory/piece_factory.hpp"
#include "../move/move.hpp"

Chessboard::~Chessboard() {
    PieceFactory::Get().UnloadTextures();
    UnloadTexture(Move::whitePromotionTexture);
    UnloadTexture(Move::blackPromotionTexture);
}

void Chessboard::initPieces() {
    const std::string fullPathWhite = "../Graphics/promoteWhite.png";
    const std::string fullPathBlack = "../Graphics/promoteBlack.png";
    const Image Wimage = LoadImage(fullPathWhite.c_str());
    const Image Bimage = LoadImage(fullPathBlack.c_str());
    Move::whitePromotionTexture  = LoadTextureFromImage(Wimage);
    Move::blackPromotionTexture  = LoadTextureFromImage(Bimage);
    UnloadImage(Wimage);
    UnloadImage(Bimage);

    for (int i = 0; i < 8; ++i) {
        grid[i+8]=Piece::Create().Pawn.black().Position(i, 1);
        grid[i+48]=Piece::Create().Pawn.white().Position(i, 6);
    }
    grid[0]=Piece::Create().Rook.black().Position(0, 0);
    grid[1]=Piece::Create().Horse.black().Position(1, 0);
    grid[2]=Piece::Create().Bishop.black().Position(2, 0);
    grid[3]=Piece::Create().Queen.black().Position(3, 0);
    grid[4]=Piece::Create().King.black().Position(4, 0);
    grid[5]=Piece::Create().Bishop.black().Position(5, 0);
    grid[6]=Piece::Create().Horse.black().Position(6, 0);
    grid[7]=Piece::Create().Rook.black().Position(7, 0);

    grid[56]=Piece::Create().Rook.white().Position(0, 7);
    grid[57]=Piece::Create().Horse.white().Position(1, 7);
    grid[58]=Piece::Create().Bishop.white().Position(2, 7);
    grid[59]=Piece::Create().Queen.white().Position(3, 7);
    grid[60]=Piece::Create().King.white().Position(4, 7);
    grid[61]=Piece::Create().Bishop.white().Position(5, 7);
    grid[62]=Piece::Create().Horse.white().Position(6, 7);
    grid[63]=Piece::Create().Rook.white().Position(7, 7);
    
    Move::SetMoves(grid, PieceColor::white);
}

void Chessboard::DrawSquares() const {
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

void Chessboard::DrawSelectedPieceDetails(const std::shared_ptr<Piece> &piece) const {
        int x = piece->position.x;
        int y = piece->position.y;
        DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, SetClickedColor(x, y));
        piece->Draw();
        DrawLegalMoves(piece);
}

void Chessboard::SetLastMovePositions(const Vector2 from, const Vector2 to) {
    lastMovePositions[0] = from;
    lastMovePositions[1] = to;
}

void Chessboard::DrawLegalMoves(const std::shared_ptr<Piece> &piece) const {
    for (auto move : piece->legalMoves) {
        const float x = move.x * cellSize + cellSize / 2;
        const float y = move.y * cellSize + cellSize / 2;
        if (grid[static_cast<int>(move.x)+move.y*8]) {
            DrawRing({x, y}, 40, 50, 0, 360, 32, Fade(BLACK, 0.1f));
        } else {
            DrawCircle(x, y, 17., Fade(BLACK, 0.1f));
        }
    }
}

void Chessboard::DrawPieces() const {
    for(const auto &piece:grid){
        if (piece) piece->Draw();
    }
}
