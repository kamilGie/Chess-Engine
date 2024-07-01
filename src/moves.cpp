#include "moves.hpp"

Sound Move::moveSound;
Sound Move::captureSound;
Sound Move::checkSound;

Move::Move() {
    InitAudioDevice();
     Move::moveSound = LoadSound("../Sounds/move.mp3");
     Move::captureSound = LoadSound("../Sounds/capture.mp3");
     Move::checkSound = LoadSound("../Sounds/move-check.mp3");
}

Move::Move(Vector2 from, Vector2 to, std::shared_ptr<Piece>& piece) : from(from), to(to), piece(piece) {
    PlaySound(moveSound);
}

void Move::MoveAnimation() {
    DrawTexture(piece->texture, from.x , from.y, WHITE);
}

void Move::MoveCalculation() {
        if (Vector2Distance(from, to) > 0.1f) {
            from = Vector2Lerp(from, to, 0.2f);
        } else {
            AnimationEnd = true;
        }
}

void Move::ExecuteMove(std::shared_ptr<Piece> (&grid)[8][8]) {
    AnimationEnd = false;
    int x = (int)to.x/cellSize;
    int y = (int)to.y/cellSize;
    enPassant(grid);
    castling(grid);

    // Move the piece to the new position
    if(grid[x][y])  CapturePiece(grid[x][y]);
    std::cout<<piece<<std::endl;
    piece->position = {(float)x, (float)y};
    piece->moveCount++;
    if (piece->getValue() == 1 && (y == 0 || y == 7)) promote(piece);
    grid[x][y] = std::move(piece);
    std::cout<<piece<<std::endl;

}

void Move::enPassant(std::shared_ptr<Piece>(&grid)[8][8]) {
    // add enemy pawn legal move  en passant
    int x = (int)to.x/cellSize;
    int y = (int)to.y/cellSize;
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
    int x = (int)to.x/cellSize;
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
    int x = to.x/cellSize;
    int y = to.y/cellSize;
    piece = (piece->color == PieceColor::black) ?  Queen::CreateBlack(x, y): piece = Queen::CreateWhite(x, y);
}

void Move::CapturePiece(std::shared_ptr<Piece>& p) {
    PlaySound(captureSound);
    p = nullptr;
}
