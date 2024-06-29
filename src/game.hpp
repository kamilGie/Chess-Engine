#pragma once
#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>
#include "memory"

#include "chessboard.hpp"
#include "piece_interfaces.hpp"
#include "pieces.cpp"

extern int cellSize;
enum class GameStatus{
    playing,
    whiteWin,
    blackWin,
    STALEMATE,
};

class Game {
   public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();

   private:
    void GameOver();
    void handleMouseClick(int x, int y);
    void MakeMove(int x, int y);
    void CapturePiece(int x, int y);
    bool IsLegalMove(float x, float y);
    void DrawLegalMoves();
    void CalculateLegalMoves(); 
    void InitPieces();
    void InitSounds();
    void addPiece(std::shared_ptr<Piece> piece);

   private:
    Sound moveSound;
    Sound captureSound;
    Sound checkSound;
    bool hasBoardChanged = false;
    Chessboard chessboard = Chessboard();
    PieceColor ColorTurn = PieceColor::white;
    std::vector<std::shared_ptr<Piece>> pieces;
    GameStatus gameStatus = GameStatus::playing;
    std::shared_ptr<Piece> clickedPiece = nullptr;
};