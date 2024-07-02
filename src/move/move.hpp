#pragma once
#include <raylib.h>

#include <memory>

class Piece;
class Chessboard;

class Move {
   public:
    Move(Vector2 from, Vector2 to, Chessboard& chessboard);
    void MoveAnimation();
    void Update();
    void ExecuteMove();

    bool winningMove = false;
    bool stalematingMove = false;
    bool animationEnd = false;

    static Sound moveSound;
    static Sound captureSound;
    static Sound checkSound;

   private:
    Vector2 from;
    Vector2 to;
    Vector2 AnimationPosition;
    Chessboard& chessboard;
    std::shared_ptr<Piece> piece;

   private:
    void CalculateLegalMoves();
    bool isKingChecked();
    void enPassantCalculation();
    bool isEnemyPawnOn(int x, int y);
    void castling();
    void promote();
    void CapturePiece(std::shared_ptr<Piece>& p);
};
