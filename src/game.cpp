#include "game.hpp"

int cellSize = 100;

Game::Game() {
    blackPieces.push_back(new KingBlack(0, 3));
    chessboard.grid[0][3] = blackPieces.back();
    blackPieces.push_back(new QueenBlack(0, 4));
    chessboard.grid[0][4] = blackPieces.back();
    blackPieces.push_back(new RookBlack(0, 0));
    chessboard.grid[0][0] = blackPieces.back();
    blackPieces.push_back(new RookBlack(0, 7));
    chessboard.grid[0][7] = blackPieces.back();
    blackPieces.push_back(new HorseBlack(0, 1));
    chessboard.grid[0][1] = blackPieces.back();
    blackPieces.push_back(new HorseBlack(0, 6));
    chessboard.grid[0][6] = blackPieces.back();
    blackPieces.push_back(new BishopBlack(0, 2));
    chessboard.grid[0][2] = blackPieces.back();
    blackPieces.push_back(new BishopBlack(0, 5));
    chessboard.grid[0][5] = blackPieces.back();

    whitePieces.push_back(new KingWhite(7, 3));
    chessboard.grid[7][3] = whitePieces.back();
    whitePieces.push_back(new QueenWhite(7, 4));
    chessboard.grid[7][4] = whitePieces.back();
    whitePieces.push_back(new RookWhite(7, 0));
    chessboard.grid[7][0] = whitePieces.back();
    whitePieces.push_back(new RookWhite(7, 7));
    chessboard.grid[7][7] = whitePieces.back();
    whitePieces.push_back(new HorseWhite(7, 1));
    chessboard.grid[7][1] = whitePieces.back();
    whitePieces.push_back(new HorseWhite(7, 6));
    chessboard.grid[7][6] = whitePieces.back();
    whitePieces.push_back(new BishopWhite(7, 2));
    chessboard.grid[7][2] = whitePieces.back();
    whitePieces.push_back(new BishopWhite(7, 5));
    chessboard.grid[7][5] = whitePieces.back();

    for (int i = 0; i < 8; ++i) {
        blackPieces.push_back(new PawnBlack(1, i));
        chessboard.grid[1][i] = blackPieces.back();
        whitePieces.push_back(new PawnWhite(6, i));
        chessboard.grid[6][i] = whitePieces.back();
    }
    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            chessboard.grid[i][j] = nullptr;
        }
    }

    InitAudioDevice();
    moveSound = LoadSound("Sounds/move.mp3");
    captureSound = LoadSound("Sounds/capture.mp3");
}

Game::~Game() {
    for (auto piece : blackPieces) {
        delete piece;
    }

    for (auto piece : whitePieces) {
        delete piece;
    }

    UnloadSound(moveSound);
    UnloadSound(captureSound);
    CloseAudioDevice();
}

void Game::Move() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        int x = GetMouseX() / cellSize;
        int y = GetMouseY() / cellSize;
        chessboard.ShowSquares();

        if (clickedPiece) {
            chessboard.grid[y][x] = clickedPiece;
            chessboard.grid[(int)clickedPiece->position.y][(int)clickedPiece->position.x] = nullptr;

            clickedPiece->position = {(float)x, (float)y};
            clickedPiece = nullptr;
            whiteTurn = !whiteTurn;
            
            PlaySound(moveSound);
        } else if (whiteTurn) {
            clickedPiece = chessboard.grid[y][x];

        } else {
            clickedPiece = chessboard.grid[y][x];
        }
    }
}

void Game::Draw() {
    chessboard.Draw();

    if (clickedPiece != nullptr) {
        DrawRectangle(clickedPiece->position.x * cellSize, clickedPiece->position.y * cellSize, cellSize, cellSize, ORANGE);
    }

    for (auto blackP : blackPieces) {
        blackP->Draw();
    }

    for (auto whiteP : whitePieces) {
        whiteP->Draw();
    }
}

void Game::Run() {
    Move();
    Draw();
}
