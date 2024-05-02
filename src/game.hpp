#pragma once
#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>

#include "chessboard.hpp"
#include "piece_interfaces.hpp"
#include "pieces.cpp"

extern int cellSize;

class Game {
   public:
    Game();
    ~Game();
    void Run();

   private:
    void processEvent();
    void handleMouseClick(int x, int y);
    void MakeMove(int x, int y);
    void CapturePiece(int x, int y);
    bool IsLegalMove(float x, float y);
    void Draw();
    void DrawLegalMoves();
    void CalculateLegalMoves(); 
    void InitPieces();
    void addPiece(Piece* piece);

   private:
    Chessboard chessboard = Chessboard();
    std::vector<Piece*> pieces;
    Piece* clickedPiece = nullptr;
    Sound moveSound;
    Sound captureSound;
    bool isWhiteTurn = true;
};