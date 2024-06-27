#include "game.hpp"

int cellSize = 100;

Game::Game() {
    InitPieces();
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

void Game::InitPieces() {
    addPiece(new RookBlack(0));
    addPiece(new HorseBlack(1));
    addPiece(new BishopBlack(2));
    addPiece(new KingBlack(3));
    addPiece(new QueenBlack(4));
    addPiece(new BishopBlack(5));
    addPiece(new HorseBlack(6));
    addPiece(new RookBlack(7));

    addPiece(new RookWhite(0));
    addPiece(new HorseWhite(1));
    addPiece(new BishopWhite(2));
    addPiece(new KingWhite(3));
    addPiece(new QueenWhite(4));
    addPiece(new BishopWhite(5));
    addPiece(new HorseWhite(6));
    addPiece(new RookWhite(7));

    for (int i = 0; i < 8; ++i) {
        addPiece(new PawnBlack(i, 1));
        addPiece(new PawnWhite(i, 6));
    }
}

void Game::addPiece(Piece* piece) {
    pieces.push_back(piece);
    chessboard.grid[(int)piece->position.x][(int)piece->position.y] = pieces.back();
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
    bool isOwnPieceClick = isPieceClick && (chessboard.grid[x][y]->color== PieceColor::white == isWhiteTurn);

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

bool Game::IsLegalMove(float x, float y) {
    return std::any_of(clickedPiece->legalMoves.begin(), clickedPiece->legalMoves.end(), [&](auto move) { return Vector2Equals(move, {x, y}); });
}

void Game::CapturePiece(int x, int y) {
    PlaySound(captureSound);
    delete chessboard.grid[x][y];
    pieces.erase(std::find(pieces.begin(), pieces.end(), chessboard.grid[x][y]));
}

void Game::MakeMove(int x, int y) {
    chessboard.lastMovePositions[0] = {clickedPiece->position.x, clickedPiece->position.y};
    chessboard.lastMovePositions[1] = {(float)x, (float)y};
    chessboard.grid[x][y] = clickedPiece;
    chessboard.grid[(int)clickedPiece->position.x][(int)clickedPiece->position.y] = nullptr;
    clickedPiece->position = {(float)x, (float)y};
    clickedPiece = nullptr;

    isWhiteTurn = !isWhiteTurn;
    PlaySound(moveSound);

    CalculateLegalMoves();
}

void Game::CalculateLegalMoves() {
    std::cout << "i start CalculateLegalMoves" << std::endl;
    for (auto p : pieces) {
        p->SetLegalMoves(chessboard.grid);
    }
    std::cout << "i end CalculateLegalMoves" << std::endl;
}

void Game::Draw() {
    chessboard.Draw();

    if (clickedPiece) {
        int x = clickedPiece->position.x;
        int y = clickedPiece->position.y;
        DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, SetClickedColor(x, y));
        DrawLegalMoves();
    };

    for (auto p : pieces) {
        p->Draw();
    }
}

void Game::DrawLegalMoves() {
    for (auto move : clickedPiece->legalMoves) {
        float x = move.x * cellSize + cellSize / 2;
        float y = move.y * cellSize + cellSize / 2;
        if (chessboard.grid[(int)move.x][(int)move.y])
            DrawRing({x, y}, 40, 50, 0, 360, 32, Fade(BLACK, 0.1f));
        else
            DrawCircle(x, y, 17, Fade(BLACK, 0.1f));
    }
}