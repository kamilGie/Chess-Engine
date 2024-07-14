#include "game.hpp"

#include <raylib.h>
#include <raymath.h>

#include <fstream>
#include <iostream>
#include <thread>

#include "ChessAI/ChessAI.hpp"
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
    std::ifstream file("../src/GameSettings.txt");
    std::string text;
    while (file >> text) {
        if (text == "PvAI") {
            file >> text;
            if (text == "true") {
                file >> text >> text;
                ai1 = new ChessAI(text == "black" ? PieceColor::black : PieceColor::white);
            }
        } else if (text == "TargetFPS") {
            int fps;
            file >> fps;
            SetTargetFPS(fps);
        } else if (text == "PvP") {
            file >> text;
        } else if (text == "AIvAI") {
            file >> text;
            if (text == "true") {
                ai1 = new ChessAI(PieceColor::white);
                ai2 = new ChessAI(PieceColor::black);
            }
        }
    }
    file.close();

    gameStatus = GameStatus::playing;
    ColorTurn = PieceColor::white;
    chessboard.initPieces();
    InitSounds();
}

Game::~Game() {
    if (ai1) delete ai1;
    if (ai2) delete ai2;
    if (move) delete move;
    UnloadSounds();
}

void Game::HandleInput() {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !move && gameStatus == GameStatus::playing) {
        int x = GetMouseX() / cellSize;
        int y = GetMouseY() / cellSize;
        bool isOwnPieceClick = chessboard.grid[x + y * 8].get() && (chessboard.grid[x + y * 8]->color == ColorTurn);
        bool isLegalMove = (clickedPiece && std::any_of(clickedPiece->legalMoves.begin(), clickedPiece->legalMoves.end(), [&](auto move) { return Vector2Equals(move, {(float)x, (float)y}); }));

        // logic on click
        if (isOwnPieceClick) {
            clickedPiece = chessboard.grid[x + y * 8];
        } else if (clickedPiece && isLegalMove) {
            move = new Move{clickedPiece->position, {(float)x, (float)y}, chessboard};
            clickedPiece = nullptr;
        }
    }
}

void Game::Update() {
    if (gameStatus != GameStatus::playing) return;

    if (move) {
        move->Update();
        if (move->animationEnd) {
            move->ExecuteMove();
            if (move->winningMove) gameStatus = (ColorTurn == PieceColor::white) ? GameStatus::whiteWin : GameStatus::blackWin;
            if (move->stalematingMove) gameStatus = GameStatus::STALEMATE;
            delete move;
            move = nullptr;
            ColorTurn = (ColorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
            clickedPiece = nullptr;
        }
    } else if (ai1 &&  AICalculateMove == false &&  ColorTurn == ai1->colorAI) {
        AICalculateMove = true;
        std::thread aiThread([&]() {
            move = ai1->GetMove(chessboard);
            if (move->promotion) move->AI_promotion = true;
            AICalculateMove = false;
        });
        aiThread.detach();
    } else if (ai2 && AICalculateMove == false &&  ColorTurn == ai2->colorAI) {
        AICalculateMove = true;
        std::thread aiThread([&]() {
            move = ai2->GetMove(chessboard);
            if (move->promotion) move->AI_promotion = true;
            AICalculateMove = false;
        });
        aiThread.detach();
    }
}

void Game::Draw() {
    BeginDrawing();

    chessboard.DrawSquares();
    chessboard.DrawPieces();
    if (clickedPiece) chessboard.DrawSelectedPieceDetails(clickedPiece);
    if (move) move->MoveAnimation();
    if (move && move->promotion && !move->AI_promotion) move->PromoteAnimation();
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