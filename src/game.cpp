#include "game.hpp"

int cellSize = 100;

Game::Game() {
    InitAudioDevice();
    InitSounds();
    InitPieces();
}

Game::~Game() {
    UnloadSound(checkSound);
    UnloadSound(moveSound);
    UnloadSound(captureSound);
    CloseAudioDevice();
}

void Game::HandleInput() {
    if (gameStatus == GameStatus::playing && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) handleMouseClick(GetMouseX() / cellSize, GetMouseY() / cellSize);
}

void Game::Update() {
    if (hasBoardChanged) {
        CalculateLegalMoves();
        hasBoardChanged = false;
    }
}

void Game::Draw() {
    BeginDrawing();
    chessboard.Draw();

    if (clickedPiece) {
        int x = clickedPiece->position.x;
        int y = clickedPiece->position.y;
        DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, SetClickedColor(x, y));
        DrawLegalMoves();
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessboard.grid[i][j]) chessboard.grid[i][j]->Draw();
        }
    }

    if (gameStatus != GameStatus::playing) {
        GameOver();
    }

    EndDrawing();
}

void Game::InitPieces() {
    for (int i = 0; i < 8; ++i) {
        chessboard.grid[i][1] = Pawn::CreateBlack(i, 1);
        chessboard.grid[i][6] = Pawn::CreateWhite(i, 6);
    }
    chessboard.grid[0][0] = Rook::CreateBlack(0, 0);
    chessboard.grid[1][0] = Horse::CreateBlack(1, 0);
    chessboard.grid[2][0] = Bishop::CreateBlack(2, 0);
    chessboard.grid[4][0] = Queen::CreateBlack(4, 0);
    chessboard.grid[3][0] = King::CreateBlack(3, 0);
    chessboard.grid[5][0] = Bishop::CreateBlack(5, 0);
    chessboard.grid[6][0] = Horse::CreateBlack(6, 0);
    chessboard.grid[7][0] = Rook::CreateBlack(7, 0);

    chessboard.grid[0][7] = Rook::CreateWhite(0, 7);
    chessboard.grid[1][7] = Horse::CreateWhite(1, 7);
    chessboard.grid[2][7] = Bishop::CreateWhite(2, 7);
    chessboard.grid[4][7] = Queen::CreateWhite(4, 7);
    chessboard.grid[3][7] = King::CreateWhite(3, 7);
    chessboard.grid[5][7] = Bishop::CreateWhite(5, 7);
    chessboard.grid[6][7] = Horse::CreateWhite(6, 7);
    chessboard.grid[7][7] = Rook::CreateWhite(7, 7);

    CalculateLegalMoves();
}

void Game::InitSounds() {
    moveSound = LoadSound("Sounds/move.mp3");
    captureSound = LoadSound("Sounds/capture.mp3");
    checkSound = LoadSound("Sounds/move-check.mp3");
}

void Game::handleMouseClick(int x, int y) {
    bool isPieceClick = chessboard.grid[x][y].get();
    bool isOwnPieceClick = isPieceClick && (chessboard.grid[x][y]->color == ColorTurn);

    if (isOwnPieceClick) {
        clickedPiece = chessboard.grid[x][y];
        return;
    }

    if (clickedPiece && IsLegalMove(x, y)) {
        if (isPieceClick) CapturePiece(x, y);
        MakeMove(x, y);
    }
}

bool Game::IsLegalMove(float x, float y) {
    return std::any_of(clickedPiece->legalMoves.begin(), clickedPiece->legalMoves.end(), [&](auto move) { return Vector2Equals(move, {x, y}); });
}

void Game::CapturePiece(int x, int y) {
    PlaySound(captureSound);
    chessboard.grid[x][y] = nullptr;
}

void Game::MakeMove(int x, int y) {
    // Store  move positions
    chessboard.lastMovePositions[0] = {clickedPiece->position.x, clickedPiece->position.y};
    chessboard.lastMovePositions[1] = {(float)x, (float)y};

    // Move the piece to the new position
    chessboard.grid[x][y] = std::move(chessboard.grid[(int)clickedPiece->position.x][(int)clickedPiece->position.y]);
    clickedPiece->position = {(float)x, (float)y};
    if (clickedPiece->getValue() == 1 && (y == 0 || y == 7)) promote(clickedPiece);
    clickedPiece->HaveMoved = true;

    // Reset the clicked piece
    clickedPiece = nullptr;

    ColorTurn = (ColorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
    PlaySound(moveSound);

    hasBoardChanged = true;
}


void Game::promote(std::shared_ptr<Piece>& piece) {
    if (piece->color == PieceColor::black) chessboard.grid[(int)piece->position.x][(int)piece->position.y] = Queen::CreateBlack(piece->position.x, piece->position.y);
    else chessboard.grid[(int)piece->position.x][(int)piece->position.y] = Queen::CreateWhite(piece->position.x, piece->position.y);
    
}

void Game::CalculateLegalMoves() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessboard.grid[i][j]) chessboard.grid[i][j]->SetLegalMoves(chessboard.grid);
        }
    }

    checkForCastling();

    bool NoPossibleMoves = std::all_of(&chessboard.grid[0][0], &chessboard.grid[0][0] + 8 * 8, [&](auto& piece) { return !piece || piece->color != ColorTurn || piece->legalMoves.empty(); });
    if (isKingChecked(chessboard.grid)) {
        PlaySound(checkSound);
        if (NoPossibleMoves) gameStatus = (ColorTurn == PieceColor::black) ? GameStatus::whiteWin : GameStatus::blackWin;
    } else if (NoPossibleMoves) {
        gameStatus = GameStatus::STALEMATE;
    }
}

void Game::checkForCastling() {
    
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

void Game::DrawLegalMoves() {
    for (auto move : clickedPiece->legalMoves) {
        float x = move.x * cellSize + cellSize / 2;
        float y = move.y * cellSize + cellSize / 2;
        if (chessboard.grid[(int)move.x][(int)move.y]) {
            DrawRing({x, y}, 40, 50, 0, 360, 32, Fade(BLACK, 0.1f));
        } else {
            DrawCircle(x, y, 17, Fade(BLACK, 0.1f));
        }
    }
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