#pragma once
#include <raylib.h>
#include <raymath.h>

#include <memory>

#include "piece_interfaces.hpp"
#include "pieces.hpp"


class Move{
    public:
    Move();
    Move(Vector2 from, Vector2 to, std::shared_ptr<Piece>& piece);
    void MoveAnimation();
    void MoveCalculation();
    void ExecuteMove(std::shared_ptr<Piece>(&grid)[8][8]);
    void enPassant(std::shared_ptr<Piece> (&grid)[8][8]);
    void castling(std::shared_ptr<Piece> (&grid)[8][8]);
    void CapturePiece(std::shared_ptr<Piece>& p);
    void promote(std::shared_ptr<Piece>& piece);
    
    Vector2 from;
    Vector2 to;
    std::shared_ptr<Piece> piece;
    bool AnimationEnd = false;

    static Sound moveSound;
    static Sound captureSound;
    static Sound checkSound;
};