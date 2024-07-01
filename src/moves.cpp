#include "moves.hpp"

Sound Move::moveSound;
Sound Move::captureSound;
Sound Move::checkSound;

Move::Move(Vector2 from, Vector2 to, Chessboard& chessboard)
    : from(from), to(to), AnimationPosition(Vector2Scale(from, cellSize)), chessboard(chessboard), piece(std::move(chessboard.grid[(int)from.x][(int)from.y])) {
    chessboard.SetLastMovePositions(from, to);
    PlaySound(moveSound);
}

void Move::MoveAnimation() {
    DrawTexture(piece->texture, AnimationPosition.x, AnimationPosition.y, WHITE);
}

void Move::Update() {
    if (Vector2Distance(AnimationPosition, Vector2Scale(to, cellSize)) > 0.1f) {
        AnimationPosition = Vector2Lerp(AnimationPosition, Vector2Scale(to, cellSize), 0.2f);
    } else {
        AnimationEnd = true;
    }
}

void Move::ExecuteMove() {
    if (piece->getValue() == 1) enPassantCalculation();
    if (piece->getValue() == 20 && abs(from.x - to.x) > 1) castling();

    if (chessboard.grid[(int)to.x][(int)to.y]) CapturePiece(chessboard.grid[(int)to.x][(int)to.y]);
    piece->position = to;
    piece->moveCount++;
    if (piece->getValue() == 1 && (to.y == 0 || to.y == 7)) promote();
    chessboard.grid[(int)to.x][(int)to.y] = std::move(piece);
}

void Move::enPassantCalculation() {
    int x = to.x;
    int y = to.y;
    int moveDirection = (piece->color == PieceColor::black) ? -1 : 1;

    if (abs(from.x - to.x) > 0 && !chessboard.grid[x][y]) CapturePiece(chessboard.grid[x][y + moveDirection]);

    if (abs(from.y - to.y) > 1) {
        if (isEnemyPawnOn(x-1, y)) std::static_pointer_cast<Pawn>(chessboard.grid[x - 1][y])->en_passant = {to.x, to.y + moveDirection};
        if (isEnemyPawnOn(x+1, y)) std::static_pointer_cast<Pawn>(chessboard.grid[x + 1][y])->en_passant = {to.x, to.y + moveDirection};
    }
}

bool Move::isEnemyPawnOn(int x, int y) {
    if (x < 0 || x > 7 || y < 0 || y > 7) return false;
    return chessboard.grid[x][y] && chessboard.grid[x][y]->getValue() == 1 && chessboard.grid[x][y]->color != piece->color;
}

void Move::castling() {
    int rookX = (to.x == 1) ? 0 : 7;
    int rookNewX = (to.x == 1) ? 2 : 4;
    int rookY = (piece->color == PieceColor::black) ? 0 : 7;
    chessboard.grid[rookNewX][rookY] = std::move(chessboard.grid[rookX][rookY]);
    chessboard.grid[rookNewX][rookY]->position = {(float)rookNewX, (float)rookY};
    chessboard.grid[rookNewX][rookY]->moveCount++;
}

void Move::promote() {
    piece = (piece->color == PieceColor::black) ? Queen::CreateBlack(to.x, to.y) : piece = Queen::CreateWhite(to.x, to.y);
}

void Move::CapturePiece(std::shared_ptr<Piece>& p) {
    PlaySound(captureSound);
    p = nullptr;
}
