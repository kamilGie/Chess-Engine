#pragma once
#include "chessboard/chessboard.hpp"
#include "stateMachine/stateMahcine.hpp"

class Piece;
class Move;
class ChessAI;
enum class PieceColor;
enum class GameStatus;

class Game :public State{
   public:
    Game(StateMachine& sm);
    ~Game();
    void Draw() override;
    void Update() override;
    void HandleInput() override;

   private:
    void GameOver();
    void LoadSettingsData();

   private:
    Move* move=nullptr;
    std::unique_ptr<ChessAI> ai1;
    std::unique_ptr<ChessAI> ai2;
    bool AIDoingMove = false;
    bool undoMovevsAi=false;
    PieceColor ColorTurn;
    GameStatus gameStatus;
    Chessboard chessboard = Chessboard();
    std::shared_ptr<Piece> clickedPiece = nullptr;
    float time = 0;
};