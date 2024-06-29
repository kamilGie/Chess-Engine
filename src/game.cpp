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

    for (auto p : pieces) {
        p->Draw();
    }

    if (gameStatus != GameStatus::playing) {
        GameOver();
    }

    EndDrawing();
}

void Game::InitPieces() {
    for (int i = 0; i < 8; ++i) {
        addPiece(Pawn::CreateBlack(i, 1));
        addPiece(Pawn::CreateWhite(i, 6));
    }
    addPiece(Rook::CreateBlack(0, 0));
    addPiece(Horse::CreateBlack(1, 0));
    addPiece(Bishop::CreateBlack(2, 0));
    addPiece(Queen::CreateBlack(4, 0));
    addPiece(Bishop::CreateBlack(5, 0));
    addPiece(Horse::CreateBlack(6, 0));
    addPiece(Rook::CreateBlack(7, 0));

    addPiece(Rook::CreateWhite(0, 7));
    addPiece(Horse::CreateWhite(1, 7));
    addPiece(Bishop::CreateWhite(2, 7));
    addPiece(Queen::CreateWhite(4, 7));
    addPiece(Bishop::CreateWhite(5, 7));
    addPiece(Horse::CreateWhite(6, 7));
    addPiece(Rook::CreateWhite(7, 7));

    // we adding to the end so the king is the last piece to be drawn and when we calculate the legal moves we can use the atackedBy arrays
    addPiece(King::CreateWhite(3, 7));
    addPiece(King::CreateBlack(3, 0));
    CalculateLegalMoves();
}

void Game::InitSounds() {
    moveSound = LoadSound("Sounds/move.mp3");
    captureSound = LoadSound("Sounds/capture.mp3");
    checkSound = LoadSound("Sounds/move-check.mp3");
}

void Game::addPiece(std::shared_ptr<Piece> piece) {
    pieces.push_back(piece);
    chessboard.grid[(int)piece->position.x][(int)piece->position.y] = piece;
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
    pieces.erase(std::find(pieces.begin(), pieces.end(), chessboard.grid[x][y]));
    chessboard.grid[x][y]=nullptr;
}

void Game::MakeMove(int x, int y) {
    // Store  move positions
    chessboard.lastMovePositions[0] = {clickedPiece->position.x, clickedPiece->position.y};
    chessboard.lastMovePositions[1] = {(float)x, (float)y};

    // Move the piece to the new position
    chessboard.grid[x][y] = std::move(chessboard.grid[(int)clickedPiece->position.x][(int)clickedPiece->position.y]);
    clickedPiece->position = {(float)x, (float)y};

    // Reset the clicked piece
    clickedPiece = nullptr;

    ColorTurn = (ColorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;
    PlaySound(moveSound);

    hasBoardChanged = true;
}

void Game::CalculateLegalMoves() {
    bool atackedPools[8][8]{};
    for (auto piece : pieces) {
        if (ColorTurn != piece->color) {
            piece->SetAtackedPools(chessboard.grid,atackedPools);
        }
    }

    std::shared_ptr<Piece> king = nullptr;
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++){
            if(chessboard.grid[i][j] && chessboard.grid[i][j]->color == ColorTurn && chessboard.grid[i][j]->getValue() == 20){
                 king = chessboard.grid[i][j];
                 break;
            }
        }
    }
    bool check = atackedPools[(int)king->position.x][(int)king->position.y];


    for (auto piece : pieces) {
        piece->SetLegalMoves(chessboard.grid);
    }
    if(check){
        PlaySound(checkSound);
        if (std::all_of(pieces.begin(), pieces.end(), [&](auto piece) { return piece->color != ColorTurn || piece->legalMoves.empty(); })) {
            gameStatus = GameStatus::blackWin;
            if (ColorTurn == PieceColor::black) gameStatus = GameStatus::whiteWin;
        }
    
    }
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