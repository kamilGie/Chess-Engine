#pragma once
#include <raylib.h>
#include <raymath.h>

#include "../chessboard/chessboard.hpp"

class Move {
   public:
    Move(Vector2 from, Vector2 to, Chessboard& chessboard);
    void MoveAnimation();
    void Update();
    void ExecuteMove();

    bool AnimationEnd = false;

    static Sound moveSound;
    static Sound captureSound;
    static Sound checkSound;

   private:
    Vector2 from;
    Vector2 to;
    Vector2 AnimationPosition;
    Chessboard& chessboard;
    std::shared_ptr<Piece> piece;

    void enPassantCalculation();
    bool isEnemyPawnOn(int x, int y);
    void castling();
    void promote();
    void CapturePiece(std::shared_ptr<Piece>& p);
};
