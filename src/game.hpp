#pragma once
#include "chessboard/chessboard.hpp"

class Piece;
class Move;
class ChessAI;
enum class PieceColor;
enum class GameStatus;

class Game {
   public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();

   private:
    void GameOver();
    void LoadSettingsData();

   private:
    Move* move=nullptr;
    std::unique_ptr<ChessAI> ai1;
    std::unique_ptr<ChessAI> ai2;
    bool AIDoingMove = false;
    PieceColor ColorTurn;
    GameStatus gameStatus;
    Chessboard chessboard = Chessboard();
    std::shared_ptr<Piece> clickedPiece = nullptr;
    float time = 0;
};