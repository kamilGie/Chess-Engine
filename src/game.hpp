#pragma once

#include <raylib.h>
#include <iostream>
#include "chessboard.hpp"
#include "piece.hpp"

class Game {
   public:
    Chessboard chessboard = Chessboard();
    Piece piece = Piece(2, 2);
    void Draw();
};