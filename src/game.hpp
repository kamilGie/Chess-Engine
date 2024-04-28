#pragma once
#include <raylib.h>
#include <iostream>
#include "chessboard.hpp"
#include "piece.hpp"
#include "pieces.cpp"
#include <vector>

extern int cellSize;

class Game {
   public:

    Game();
    ~Game();

    Chessboard chessboard = Chessboard();
    std::vector <Piece*> blackPieces;
    std::vector <Piece*> whitePieces;
    Piece*  clickedPiece=nullptr;
    bool whiteTurn=true;
    void Move();
    void Draw();
};