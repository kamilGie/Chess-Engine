#pragma once
#include <raylib.h>
#include <raymath.h>

#include <memory>

#include "piece_interfaces.hpp"

class Move {
   public:
    Move(Vector2 from, Vector2 to, std::shared_ptr<Piece> piece) : from(from), to(to), piece(piece){};
    void MoveAnimation();
    bool MoveCalculation();
    Vector2 from;
    Vector2 to;
    std::shared_ptr<Piece> piece;
};