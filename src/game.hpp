#pragma once
#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <memory>

#include "move/move.hpp"

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
    bool IsLegalMove(float x, float y);
    void CalculateLegalMoves(); 
    void InitPieces();
    void InitSounds();
    void UnloadSounds();
    bool isKingChecked(std::shared_ptr<Piece> grid[][8]);

   private:
    Chessboard chessboard = Chessboard();
    PieceColor ColorTurn = PieceColor::white;
    GameStatus gameStatus = GameStatus::playing;
    std::shared_ptr<Piece> clickedPiece = nullptr;
    std::unique_ptr<Move> move = nullptr;
};