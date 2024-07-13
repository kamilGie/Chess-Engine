#include "move.hpp"

#include <raymath.h>

#include <iostream>

#include "../chessboard/chessboard.hpp"
#include "../pieces/factory/piece_factory.hpp"
#include "../pieces/models/include.hpp"

Sound Move::moveSound;
Sound Move::captureSound;
Sound Move::checkSound;
Texture2D Move::whitePromotionTexture;
Texture2D Move::blackPromotionTexture;

Move::Move(Vector2 from, Vector2 to, Chessboard& chessboard)
    : from(from), to(to), AnimationPosition(Vector2Scale(from, cellSize)), chessboard(chessboard), piece(std::move(chessboard.grid[(int)from.x+from.y*8])) {
    chessboard.SetLastMovePositions(from, to);
    PlaySound(moveSound);
    if (piece->getValue() == 1 && (to.y == 0 || to.y == 7)) promotion = true;
}

void Move::MoveAnimation() {
    DrawTexture(piece->texture, AnimationPosition.x, AnimationPosition.y, WHITE);
}

void Move::PromoteAnimation() {
    if (piece->color == PieceColor::white) DrawTexture(whitePromotionTexture, to.x * cellSize, to.y * cellSize, WHITE);
    if (piece->color == PieceColor::black) DrawTexture(blackPromotionTexture, to.x * cellSize, to.y * cellSize - (3 * cellSize), WHITE);
}

void Move::Update() {
    if (Vector2Distance(AnimationPosition, Vector2Scale(to, cellSize)) > 0.1f) {
        AnimationPosition = Vector2Lerp(AnimationPosition, Vector2Scale(to, cellSize), 20 * GetFrameTime());
    } else if (promotion) {
        promote();
    } else {
        animationEnd = true;
    }
}

void Move::ExecuteMove() {
    if (piece->getValue() == 1) enPassantCalculation();
    if (piece->getValue() == 100 && abs(from.x - to.x) > 1) castling();

    if (chessboard.grid[(int)to.x+to.y*8]) CapturePiece(chessboard.grid[(int)to.x+to.y*8]);
    piece->position = to;
    piece->moveCount++;
    chessboard.grid[(int)to.x+to.y*8] = piece;
    CalculateLegalMoves();
}

void Move::SetMoves(std::array<std::shared_ptr<Piece>, 64> grid, PieceColor color) {
    std::shared_ptr<King> king = nullptr;
    for (auto p : grid) {
        if (p && p->color == color) {
            p->SetMoves(grid);
            if (!king && p->getValue() == 100) king = std::static_pointer_cast<King>(p);
        }
    }
    king->SetLegalMoves(grid);
}

void Move::enPassantCalculation() {
    int x = to.x;
    int y = to.y;
    int moveDirection = (piece->color == PieceColor::black) ? -1 : 1;

    if (abs(from.x - to.x) > 0 && !chessboard.grid[x+y*8]) CapturePiece(chessboard.grid[x + ((y + moveDirection)*8)]);

    if (abs(from.y - to.y) > 1) {
        if (isEnemyPawnOn(x - 1, y)) std::static_pointer_cast<Pawn>(chessboard.grid[x - 1 + y*8])->en_passant = {to.x, to.y + moveDirection};
        if (isEnemyPawnOn(x + 1, y)) std::static_pointer_cast<Pawn>(chessboard.grid[x + 1+y*8])->en_passant = {to.x, to.y + moveDirection};
    }
}

bool Move::isEnemyPawnOn(int x, int y) {
    if (x < 0 || x > 7 || y < 0 || y > 7) return false;
    return chessboard.grid[x+y*8] && chessboard.grid[x+y*8]->getValue() == 1 && chessboard.grid[x+y*8]->color != piece->color;
}

void Move::castling() {
    int rookX = (to.x == 1) ? 0 : 7;
    int rookNewX = (to.x == 1) ? 2 : 4;
    int rookY = (piece->color == PieceColor::black) ? 0 : 7;
    chessboard.grid[rookNewX + rookY*8] = std::move(chessboard.grid[rookX+rookY*8]);
    chessboard.grid[rookNewX+rookY*8]->position = {(float)rookNewX, (float)rookY};
    chessboard.grid[rookNewX+rookY*8]->moveCount++;
}

void Move::promote() {
    if (AI_promotion) {
        piece = piece->color == PieceColor::white ? Piece::Create().Queen.white().Position(to.x, to.y) : Piece::Create().Queen.black().Position(to.x, to.y);
        promotion = false;
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() / cellSize == to.x && GetMouseY() / cellSize >= to.y && GetMouseY() / cellSize < to.y + 4) {
        int y = GetMouseY() / cellSize;
        if (y == 0) piece = Piece::Create().Queen.white().Position(to.x, to.y);
        if (y == 1) piece = Piece::Create().Rook.white().Position(to.x, to.y);
        if (y == 2) piece = Piece::Create().Horse.white().Position(to.x, to.y);
        if (y == 3) piece = Piece::Create().Bishop.white().Position(to.x, to.y);

        if (y == 7) piece = Piece::Create().Queen.black().Position(to.x, to.y);
        if (y == 6) piece = Piece::Create().Rook.black().Position(to.x, to.y);
        if (y == 5) piece = Piece::Create().Horse.black().Position(to.x, to.y);
        if (y == 4) piece = Piece::Create().Bishop.black().Position(to.x, to.y);

        promotion = false;
    }
}

void Move::CapturePiece(std::shared_ptr<Piece>& p) {
    PlaySound(captureSound);
    p = nullptr;
}

void Move::CalculateLegalMoves() {
    PieceColor eneymyColor = piece->color == PieceColor::white ? PieceColor::black : PieceColor::white;
    SetMoves(chessboard.grid, eneymyColor);

    bool NoPossibleMoves = std::all_of(&chessboard.grid[0], &chessboard.grid[64], [this](auto p) { return !p || p->color == piece->color ||  p->legalMoves.empty(); });

    if (isKingChecked()) {
        PlaySound(checkSound);
        if (NoPossibleMoves) winningMove = true;
    } else if (NoPossibleMoves) {
        stalematingMove = true;
    }
}

bool Move::isKingChecked() {
    for(auto p : chessboard.grid){
            if (p && p->color != piece->color && p->getValue() == 100) {
                if (std::static_pointer_cast<King>(p)->isGettingAtack(chessboard.grid))
                    return true;
                else
                    return false;
            }
        }
    return false;
}
