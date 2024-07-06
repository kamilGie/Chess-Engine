#include "game.hpp"

#include <raylib.h>
#include <raymath.h>

#include "chessboard/chessboard.hpp"
#include "move/move.hpp"
#include "pieces/models/include.hpp"
#include "resources/audio.hpp"

int cellSize = 100;

enum class GameStatus {
    playing,
    whiteWin,
    blackWin,
    STALEMATE,
};

Game::Game() {
    gameStatus = GameStatus::playing;
    ColorTurn = PieceColor::white;
    chessboard.initPieces();
    InitSounds();
}

Game::~Game() {
    UnloadSounds();
}

void Game::HandleInput() {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !move && gameStatus == GameStatus::playing) {
        int x = GetMouseX() / cellSize;
        int y = GetMouseY() / cellSize;
        bool isOwnPieceClick = chessboard.grid[x][y].get() && (chessboard.grid[x][y]->color == ColorTurn);
        bool isLegalMove = (clickedPiece && std::any_of(clickedPiece->legalMoves.begin(), clickedPiece->legalMoves.end(), [&](auto move) { return Vector2Equals(move, {(float)x, (float)y}); }));

        //logic on click 
        if (isOwnPieceClick){
            clickedPiece = chessboard.grid[x][y];
        }else if (clickedPiece && isLegalMove) {
            move = new Move{clickedPiece->position, {(float)x, (float)y}, chessboard};
            clickedPiece = nullptr;
        }
    }
}

void Game::Update() {
    if (move) {
        move->Update();
        if (move->animationEnd) {
            move->ExecuteMove();
            if (move->winningMove) gameStatus = (ColorTurn == PieceColor::white) ? GameStatus::whiteWin : GameStatus::blackWin;
            if (move->stalematingMove) gameStatus = GameStatus::STALEMATE;
            delete move;
            move = nullptr;
            ColorTurn = (ColorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
        }
    }
}

void Game::Draw() {
    BeginDrawing();

    chessboard.DrawSquares();
    chessboard.DrawPieces();
    if (clickedPiece) chessboard.DrawSelectedPieceDetails(clickedPiece);
    if (move) move->MoveAnimation();
    if (gameStatus != GameStatus::playing) GameOver();

    EndDrawing();
}

void Game::GameOver() {
    std::string resultText;
    switch (gameStatus) {
        case GameStatus::whiteWin:
            resultText = "WHITE WINS";
            break;
        case GameStatus::blackWin:
            resultText = "BLACK WINS";
            break;
        case GameStatus::STALEMATE:
            resultText = "STALEMATE";
            break;
        default:
            break;
    }

    DrawRectangle(0, 0, 800, 800, Fade(BLACK, 0.8f));
    DrawText("GAME OVER", (800 - MeasureText("GAME OVER", 50)) / 2, 300, 50, WHITE);
    DrawText(resultText.c_str(), (800 - MeasureText(resultText.c_str(), 50)) / 2, 380, 50, WHITE);
}