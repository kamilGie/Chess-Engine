#pragma once
#include "chessboard/chessboard.hpp"
#include "ChessAI/ChessAI.hpp"

class Piece;
class Move;
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

   private:
    ChessAI ai = ChessAI();
    Move* move = nullptr;
    PieceColor ColorTurn;
    GameStatus gameStatus;
    Chessboard chessboard = Chessboard();
    std::shared_ptr<Piece> clickedPiece = nullptr;
};