#include "moves.hpp"

Sound Move::moveSound;
Sound Move::captureSound;
Sound Move::checkSound;


Move::Move(Vector2 from, Vector2 to, Chessboard& chessboard): from(from), to(to), chessboard(chessboard){
    piece = chessboard.grid[(int)from.x][(int)from.y];
    chessboard.grid[(int)from.x][(int)from.y] = nullptr;
    chessboard.lastMovePositions[0] = from;
    chessboard.lastMovePositions[1] = to;
    AnimationPosition = Vector2Scale(from, cellSize);
    PlaySound(moveSound);
}

void Move::MoveAnimation() {
    DrawTexture(piece->texture, AnimationPosition.x , AnimationPosition.y, WHITE);
}

void Move::Update() {
        if (Vector2Distance(AnimationPosition, Vector2Scale(to, cellSize)) > 0.1f) {
            AnimationPosition = Vector2Lerp(AnimationPosition, Vector2Scale(to, cellSize),0.2f);
        } else {
            AnimationEnd = true;
        }
}

void Move::ExecuteMove(std::shared_ptr<Piece> (&grid)[8][8]) {
    enPassant(grid);
    castling(grid);

    int x = to.x;
    int y = to.y;
    if(grid[x][y])  CapturePiece(grid[x][y]);
    std::cout<<piece<<std::endl;
    piece->position = {(float)x, (float)y};
    piece->moveCount++;
    if (piece->getValue() == 1 && (y == 0 || y == 7)) promote(piece);
    grid[x][y] = std::move(piece);
    AnimationEnd = false;
}

void Move::enPassant(std::shared_ptr<Piece>(&grid)[8][8]) {
    // add enemy pawn legal move  en passant
    int x = to.x;
    int y = to.y;
    if (piece->getValue() == 1 && abs(piece->position.y - y)>1){
        if(x>0 && grid[x-1][y] && grid[x-1][y]->getValue() == 1 && grid[x-1][y]->color != piece->color){
            int moveDirection = (piece->color == PieceColor::black) ? -1 : 1;
            std::dynamic_pointer_cast<Pawn>(grid[x-1][y])->en_passant = {(float)x,(float)y+moveDirection}; 
        }
        if(x<7 && grid[x+1][y] && grid[x+1][y]->getValue() == 1 && grid[x+1][y]->color != piece->color){
            int moveDirection = (piece->color == PieceColor::black) ? -1 : 1;
            std::dynamic_pointer_cast<Pawn>(grid[x+1][y])->en_passant = {(float)x,(float)y+moveDirection};
        }
    }

    // capture enemy pawn en passant
    if(piece->getValue() == 1 && abs(piece->position.x - x)>0 && !grid[x][y]){
        int moveDirection = (piece->color == PieceColor::black) ? -1 : 1;
        CapturePiece(grid[x][y+moveDirection]);
    }
}

void Move::castling(std::shared_ptr<Piece>(&grid)[8][8]) {
    int x = to.x;
    if (piece->getValue() == 20 && abs(piece->position.x - x)>1) {
        int rookX = (x == 1) ? 0 : 7;
        int rookNewX = (x == 1) ? 2 : 4;
        int rookY = (piece->color == PieceColor::black) ? 0 : 7;
        grid[rookNewX][rookY] = std::move(grid[rookX][rookY]);
        grid[rookNewX][rookY]->position = {(float)rookNewX, (float)rookY};
        grid[rookNewX][rookY]->moveCount++;
    }
}

void Move::promote(std::shared_ptr<Piece>& piece) {
    piece = (piece->color == PieceColor::black) ?  Queen::CreateBlack(to.x, to.y): piece = Queen::CreateWhite(to.x, to.y);
}

void Move::CapturePiece(std::shared_ptr<Piece>& p) {
    PlaySound(captureSound);
    p = nullptr;
}
