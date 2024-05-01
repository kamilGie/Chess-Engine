#include "game.hpp"

int cellSize = 100;

Game::Game() {
    pieces.push_back(new KingBlack(3,0));
    chessboard.grid[3][0] = pieces.back();
    pieces.push_back(new QueenBlack(4,0));
    chessboard.grid[4][0] = pieces.back();
    pieces.push_back(new RookBlack(0,0));
    chessboard.grid[0][0] = pieces.back();
    pieces.push_back(new RookBlack(7,0));
    chessboard.grid[7][0] = pieces.back();
    pieces.push_back(new HorseBlack(1,0));
    chessboard.grid[1][0] = pieces.back();
    pieces.push_back(new HorseBlack(6,0));
    chessboard.grid[6][0] = pieces.back();
    pieces.push_back(new BishopBlack(2,0));
    chessboard.grid[2][0] = pieces.back();
    pieces.push_back(new BishopBlack(5,0));
    chessboard.grid[5][0] = pieces.back();

    pieces.push_back(new KingWhite(3,7));
    chessboard.grid[3][7] = pieces.back();
    pieces.push_back(new QueenWhite(4,7));
    chessboard.grid[4][7] = pieces.back();
    pieces.push_back(new RookWhite(0,7));
    chessboard.grid[0][7] = pieces.back();
    pieces.push_back(new RookWhite(7,7));
    chessboard.grid[7][7] = pieces.back();
    pieces.push_back(new HorseWhite(1,7));
    chessboard.grid[1][7] = pieces.back();
    pieces.push_back(new HorseWhite(6,7));
    chessboard.grid[6][7] = pieces.back();
    pieces.push_back(new BishopWhite(2,7));
    chessboard.grid[2][7] = pieces.back();
    pieces.push_back(new BishopWhite(5,7));
    chessboard.grid[5][7] = pieces.back();

    for (int i = 0; i < 8; ++i) {
        pieces.push_back(new PawnBlack(i,1));
        chessboard.grid[i][1] = pieces.back();
        pieces.push_back(new PawnWhite(i,6));
        chessboard.grid[i][6] = pieces.back();
    }
    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            chessboard.grid[j][i] = nullptr;
        }
    }

    InitAudioDevice();
    moveSound = LoadSound("Sounds/move.mp3");
    captureSound = LoadSound("Sounds/capture.mp3");
    CalculateLegalMoves();
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
    bool isPieceClick = chessboard.grid[x][y];
    bool isOwnPieceClick = isPieceClick && chessboard.grid[x][y]->whiteColor() == isWhiteTurn;

    if (isOwnPieceClick) {
        clickedPiece = chessboard.grid[x][y];
        return;
    }

    if (clickedPiece && IsLegalMove(x, y)) {
        if (isPieceClick) {
            CapturePiece(x, y);
        }
        MakeMove(x, y);
    }
}

bool Game::IsLegalMove(int x, int y) {
    for(auto move : clickedPiece->legalMoves){
        if(Vector2Equals(move ,{(float)x,(float)y}))
        return true;
    }
    return false;
}

void Game::CapturePiece(int x, int y) {
    PlaySound(captureSound);
    delete chessboard.grid[x][y];
    pieces.erase(std::find(pieces.begin(), pieces.end(), chessboard.grid[x][y]));
}

void Game::MakeMove(int x, int y) {
    lastMovePositions[0] = {clickedPiece->position.x, clickedPiece->position.y};
    lastMovePositions[1] = {(float)x, (float)y};
    chessboard.grid[x][y] = clickedPiece;
    chessboard.grid[(int)clickedPiece->position.x][(int)clickedPiece->position.y] = nullptr;
    clickedPiece->position = {(float)x, (float)y};
    clickedPiece = nullptr;

    isWhiteTurn = !isWhiteTurn;
    PlaySound(moveSound);

    CalculateLegalMoves();
}

void Game::CalculateLegalMoves() {
    for (auto p : pieces) {
        p->SetLegalMoves(chessboard.grid);
    }
}

void Game::Draw() {
    chessboard.Draw();

    DrawRectangle(lastMovePositions[0].x * cellSize, lastMovePositions[0].y * cellSize, cellSize, cellSize, SetClickedColor(lastMovePositions[0].x, lastMovePositions[0].y));
    DrawRectangle(lastMovePositions[1].x * cellSize, lastMovePositions[1].y * cellSize, cellSize, cellSize, SetClickedColor(lastMovePositions[1].x, lastMovePositions[1].y));

    if (clickedPiece) {
        DrawRectangle(clickedPiece->position.x * cellSize, clickedPiece->position.y * cellSize, cellSize, cellSize, SetClickedColor(clickedPiece->position.x, clickedPiece->position.y));
        for (auto move : clickedPiece->legalMoves) {
            if (chessboard.grid[(int)move.x][(int)move.y])
                DrawRing({move.x * cellSize + cellSize / 2, move.y * cellSize + cellSize / 2},40, 50, 0, 360, 32, Fade(BLACK, 0.1f));
            else
                DrawCircle(move.x * cellSize + cellSize / 2, move.y * cellSize + cellSize / 2, 17, Fade(BLACK, 0.1f));
        }
    }

    for (auto p : pieces) {
        p->Draw();
    }
}