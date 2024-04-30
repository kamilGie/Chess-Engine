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
    std::vector<Piece*> pieces;
    Piece* clickedPiece = nullptr;
    Sound moveSound;
    Sound captureSound;
    bool isWhiteTurn = true;
    Vector2 lastMovePositions[2]{{9,9},{9,9}};

    void processEvent();
    void handleMouseClick(int x,int y);
    void MakeMove(int x,int y);
    void CapturePiece(int x,int y);
    bool IsLegalMove(int x,int y);
    void Draw();
};