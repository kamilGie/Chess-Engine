#pragma once
#include <raylib.h>
#include <raymath.h>

#include <memory>

#include "chessboard.hpp"
#include "piece_interfaces.hpp"
#include "pieces.hpp"


class Move{
    public:
    Move(Vector2 from, Vector2 to, Chessboard& chessboard);
    void MoveAnimation();
    void Update();
    void ExecuteMove(std::shared_ptr<Piece>(&grid)[8][8]);
    void enPassant(std::shared_ptr<Piece> (&grid)[8][8]);
    void castling(std::shared_ptr<Piece> (&grid)[8][8]);
    void CapturePiece(std::shared_ptr<Piece>& p);
    void promote(std::shared_ptr<Piece>& piece);
    
    Vector2 from;
    Vector2 to;
    Vector2 AnimationPosition;
    Chessboard &chessboard;
    bool AnimationEnd = false;

    std::shared_ptr<Piece> piece;

    static Sound moveSound;
    static Sound captureSound;
    static Sound checkSound;
};
