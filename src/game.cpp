#include "game.hpp"

int cellSize = 100;

Game::Game() {
    pieces.push_back(new KingBlack(0, 3));
    chessboard.grid[0][3] = pieces.back();
    pieces.push_back(new QueenBlack(0, 4));
    chessboard.grid[0][4] = pieces.back();
    pieces.push_back(new RookBlack(0, 0));
    chessboard.grid[0][0] = pieces.back();
    pieces.push_back(new RookBlack(0, 7));
    chessboard.grid[0][7] = pieces.back();
    pieces.push_back(new HorseBlack(0, 1));
    chessboard.grid[0][1] = pieces.back();
    pieces.push_back(new HorseBlack(0, 6));
    chessboard.grid[0][6] = pieces.back();
    pieces.push_back(new BishopBlack(0, 2));
    chessboard.grid[0][2] = pieces.back();
    pieces.push_back(new BishopBlack(0, 5));
    chessboard.grid[0][5] = pieces.back();

    pieces.push_back(new KingWhite(7, 3));
    chessboard.grid[7][3] = pieces.back();
    pieces.push_back(new QueenWhite(7, 4));
    chessboard.grid[7][4] = pieces.back();
    pieces.push_back(new RookWhite(7, 0));
    chessboard.grid[7][0] = pieces.back();
    pieces.push_back(new RookWhite(7, 7));
    chessboard.grid[7][7] = pieces.back();
    pieces.push_back(new HorseWhite(7, 1));
    chessboard.grid[7][1] = pieces.back();
    pieces.push_back(new HorseWhite(7, 6));
    chessboard.grid[7][6] = pieces.back();
    pieces.push_back(new BishopWhite(7, 2));
    chessboard.grid[7][2] = pieces.back();
    pieces.push_back(new BishopWhite(7, 5));
    chessboard.grid[7][5] = pieces.back();

    for (int i = 0; i < 8; ++i) {
        pieces.push_back(new PawnBlack(1, i));
        chessboard.grid[1][i] = pieces.back();
        pieces.push_back(new PawnWhite(6, i));
        chessboard.grid[6][i] = pieces.back();
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
    for (auto p : pieces) {
        delete p;
    }

    UnloadSound(moveSound);
    UnloadSound(captureSound);
    CloseAudioDevice();
}

void Game::Run() {
    processEvent();
    Draw();
}

void Game::processEvent() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        handleMouseClick(GetMouseX() / cellSize, GetMouseY() / cellSize);
        chessboard.ShowSquares();
    }
}

void Game::handleMouseClick(int x, int y) {
    bool isPieceClick = chessboard.grid[y][x];
    bool isOwnPieceClick = isPieceClick && chessboard.grid[y][x]->whiteColor() == whiteTurn;

    if (isOwnPieceClick) {
        clickedPiece = chessboard.grid[y][x];
        return;
    } 

    if (clickedPiece) {
        if (isPieceClick) {
            CapturePiece(x, y);
        }
        MakeMove(x, y);
    }
}

void Game::CapturePiece(int x, int y) {
    PlaySound(captureSound);
    delete chessboard.grid[y][x];
    pieces.erase(std::find(pieces.begin(), pieces.end(), chessboard.grid[y][x]));
}

void Game::MakeMove(int x, int y) {
    chessboard.grid[y][x] = clickedPiece;
    chessboard.grid[(int)clickedPiece->position.y][(int)clickedPiece->position.x] = nullptr;
    clickedPiece->position = {(float)x, (float)y};
    clickedPiece = nullptr;

    whiteTurn = !whiteTurn;
    PlaySound(moveSound);
}

void Game::Draw() {
    chessboard.Draw();

    if (clickedPiece) {
        DrawRectangle(clickedPiece->position.x * cellSize, clickedPiece->position.y * cellSize, cellSize, cellSize, ORANGE);
    }

    for (auto p : pieces) {
        p->Draw();
    }
}
