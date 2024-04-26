#pragma once

#include <raylib.h>
#include <iostream>
#include "chessboard.hpp"
#include "piece.hpp"
#include "pieces.cpp"

class Game {
   public:
    Chessboard chessboard = Chessboard();
    Horse horse = Horse(1,1,WHITE);
    void Draw();
};