#pragma once
#include "chessboard/chessboard.hpp"

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
    void handleMouseClick(int x, int y);
    bool IsLegalMove(float x, float y);
    void CalculateLegalMoves();
    void InitPieces();
    void InitSounds();
    void UnloadSounds();
    bool isKingChecked(std::shared_ptr<Piece> grid[][8]);

   private:
    Move* move = nullptr;
    PieceColor ColorTurn;
    GameStatus gameStatus;
    Chessboard chessboard = Chessboard();
    std::shared_ptr<Piece> clickedPiece = nullptr;
};