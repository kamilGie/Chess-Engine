#pragma once
#include <raylib.h>
#include <raymath.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "chessboard.hpp"
#include "piece.hpp"
#include "pieces.cpp"

extern int cellSize;

class Game {
   public:
    void Run();
    Game();
    ~Game();

   private:
    Chessboard chessboard = Chessboard();
    std::vector<Piece*> blackPieces;
    std::vector<Piece*> whitePieces;
    Piece* clickedPiece = nullptr;
    Sound moveSound;
    Sound captureSound;
    bool whiteTurn = true;
    void Move();
    void WhiteMove(int x,int y);
    void BlackMove(int x,int y);
    void MakeMove(int x,int y);
    void Draw();
};