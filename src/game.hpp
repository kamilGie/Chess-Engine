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
    void enPassant(int x, int y);
    void castling(int x, int y);
    void promote(std::shared_ptr<Piece>& piece);
    void CapturePiece(int x, int y);
    bool IsLegalMove(float x, float y);
    void DrawLegalMoves();
    void CalculateLegalMoves(); 
    void InitPieces();
    void InitSounds();
    bool isKingChecked(std::shared_ptr<Piece> grid[][8]);

   private:
    Sound moveSound;
    Sound captureSound;
    Sound checkSound;
    bool hasBoardChanged = false;
    Chessboard chessboard = Chessboard();
    PieceColor ColorTurn = PieceColor::white;
    GameStatus gameStatus = GameStatus::playing;
    std::shared_ptr<Piece> clickedPiece = nullptr;
};