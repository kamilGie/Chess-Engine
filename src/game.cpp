#include "game.hpp"
#include <raylib.h>
#include <raymath.h>

#include "chessboard/chessboard.hpp"
#include "pieces/pieces.hpp"
#include "move/move.hpp"

int cellSize = 100;

enum class GameStatus {
    playing,
    whiteWin,
    blackWin,
    STALEMATE,
};

Game::Game() {
    gameStatus = GameStatus::playing;
    InitPieces();
    InitSounds();
}

Game::~Game() {
    UnloadSounds();
}

void Game::HandleInput() {
    if (gameStatus == GameStatus::playing  && !move && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
         handleMouseClick(GetMouseX() / cellSize, GetMouseY() / cellSize);
    }
}

void Game::Update() {
    if(move){
        move->Update();
        if (move->AnimationEnd) {
            move->ExecuteMove();
            ColorTurn = (ColorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
            CalculateLegalMoves();
            delete move;
            move = nullptr;
        }
    }
}

void Game::Draw() {
    BeginDrawing();

    chessboard.DrawSquares();
    chessboard.DrawPieces();
    if (clickedPiece) chessboard.DrawSelectedPieceDetails(clickedPiece);
    if (move)  move->MoveAnimation();
    if (gameStatus != GameStatus::playing) GameOver();
    
    EndDrawing();
}

void Game::InitPieces() {
    ColorTurn = PieceColor::white;
    chessboard = Chessboard();
    chessboard.initPieces();
    CalculateLegalMoves();
}

void Game::handleMouseClick(int x, int y) {
    bool isOwnPieceClick = chessboard.grid[x][y].get() && (chessboard.grid[x][y]->color == ColorTurn);
    if (isOwnPieceClick) clickedPiece = chessboard.grid[x][y];
    else if (clickedPiece && IsLegalMove(x, y)) {
        move = new Move{clickedPiece->position, {(float)x, (float)y}, chessboard};
        clickedPiece = nullptr;
    }
}

bool Game::IsLegalMove(float x, float y) {
    return std::any_of(clickedPiece->legalMoves.begin(), clickedPiece->legalMoves.end(), [&](auto move) { return Vector2Equals(move, {x, y}); });
}

void Game::CalculateLegalMoves() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessboard.grid[i][j] && chessboard.grid[i][j]->color == ColorTurn ) chessboard.grid[i][j]->SetLegalMoves(chessboard.grid);
        }
    }


    bool NoPossibleMoves = std::all_of(&chessboard.grid[0][0], &chessboard.grid[0][0] + 8 * 8, [&](auto& piece) { return !piece || piece->color != ColorTurn || piece->legalMoves.empty(); });
    if (isKingChecked(chessboard.grid)) {
        PlaySound(Move::checkSound);
        if (NoPossibleMoves) gameStatus = (ColorTurn == PieceColor::black) ? GameStatus::whiteWin : GameStatus::blackWin;
    } else if (NoPossibleMoves) {
        gameStatus = GameStatus::STALEMATE;
    }
}

bool Game::isKingChecked(std::shared_ptr<Piece> grid[][8]) {
    bool atackedPools[8][8]{};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessboard.grid[i][j] && chessboard.grid[i][j]->color != ColorTurn && chessboard.grid[i][j]->SetAtackedPools(chessboard.grid, atackedPools)) return true; 
        }
    }
    return false;
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


void Game::InitSounds() {
    InitAudioDevice();
    Move::moveSound = LoadSound("../Sounds/move.mp3");
    Move::captureSound = LoadSound("../Sounds/capture.mp3");
    Move::checkSound = LoadSound("../Sounds/move-check.mp3");
}

void Game::UnloadSounds() {
    UnloadSound(Move::checkSound);
    UnloadSound(Move::moveSound);
    UnloadSound(Move::captureSound);
    CloseAudioDevice();
}