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
    if (gameStatus == GameStatus::playing  && eventAnimation ==EventAnimation::none && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) handleMouseClick(GetMouseX() / cellSize, GetMouseY() / cellSize);
}

void Game::Update() {
    if (hasBoardChanged) {
        CalculateLegalMoves();
        hasBoardChanged = false;
    }

    if(eventAnimation == EventAnimation::move) {
        if (Vector2Distance(move.from, move.to) > 0.1f) {
            move.from = Vector2Lerp(move.from, move.to, 0.2f);
        } else {
            eventAnimation = EventAnimation::none;
            MakeMove(move.to.x/cellSize, move.to.y/cellSize);
        }
    }
    
}

void Game::Draw() {
    BeginDrawing();
    chessboard.Draw();

    if (clickedPiece && eventAnimation == EventAnimation::none) {
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

    if (gameStatus != GameStatus::playing) GameOver();
    if (eventAnimation == EventAnimation::move)  DrawTexture(move.piece->texture, move.from.x , move.from.y, WHITE);
    
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
    moveSound = LoadSound("../Sounds/move.mp3");
    captureSound = LoadSound("../Sounds/capture.mp3");
    checkSound = LoadSound("../Sounds/move-check.mp3");
}

void Game::handleMouseClick(int x, int y) {
    bool isPieceClick = chessboard.grid[x][y].get();
    bool isOwnPieceClick = isPieceClick && (chessboard.grid[x][y]->color == ColorTurn);

    if (isOwnPieceClick) clickedPiece = chessboard.grid[x][y];
    else if (clickedPiece && IsLegalMove(x, y)) {
        eventAnimation = EventAnimation::move;
        PlaySound(moveSound);
        chessboard.lastMovePositions[0] = {clickedPiece->position.x, clickedPiece->position.y};
        chessboard.lastMovePositions[1] = {(float)x, (float)y};
        move = {{clickedPiece->position.x*cellSize,clickedPiece->position.y*cellSize}, {(float)x*cellSize, (float)y*cellSize}, clickedPiece};
        chessboard.grid[(int)clickedPiece->position.x][(int)clickedPiece->position.y] = nullptr;
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
    enPassant(x, y);
    castling(x, y);

    // Move the piece to the new position
    if(chessboard.grid[x][y])  CapturePiece(x, y);
    chessboard.grid[x][y] = std::move(move.piece);
    clickedPiece->position = {(float)x, (float)y};
    clickedPiece->moveCount++;
    if (clickedPiece->getValue() == 1 && (y == 0 || y == 7)) promote(clickedPiece);

    // Reset the clicked piece
    clickedPiece = nullptr;

    ColorTurn = (ColorTurn == PieceColor::white) ? PieceColor::black : PieceColor::white;

    hasBoardChanged = true;
}

void Game::enPassant(int x, int y) {
    // add enemy pawn legal move  en passant
    if (clickedPiece->getValue() == 1 && abs(clickedPiece->position.y - y)>1){
        if(x>0 && chessboard.grid[x-1][y] && chessboard.grid[x-1][y]->getValue() == 1 && chessboard.grid[x-1][y]->color != clickedPiece->color){
            int moveDirection = (clickedPiece->color == PieceColor::black) ? -1 : 1;
            std::dynamic_pointer_cast<Pawn>(chessboard.grid[x-1][y])->en_passant = {(float)x,(float)y+moveDirection}; 
        }
        if(x<7 && chessboard.grid[x+1][y] && chessboard.grid[x+1][y]->getValue() == 1 && chessboard.grid[x+1][y]->color != clickedPiece->color){
            int moveDirection = (clickedPiece->color == PieceColor::black) ? -1 : 1;
            std::dynamic_pointer_cast<Pawn>(chessboard.grid[x+1][y])->en_passant = {(float)x,(float)y+moveDirection};
        }
    }

    // capture enemy pawn en passant
    if(clickedPiece->getValue() == 1 && abs(clickedPiece->position.x - x)>0 && !chessboard.grid[x][y]){
        int moveDirection = (clickedPiece->color == PieceColor::black) ? -1 : 1;
        CapturePiece(x,y+moveDirection);
    }
}

void Game::castling(int x, int y) {
    if (clickedPiece->getValue() == 20 && abs(clickedPiece->position.x - x)>1) {
        int rookX = (x == 1) ? 0 : 7;
        int rookNewX = (x == 1) ? 2 : 4;
        int rookY = (clickedPiece->color == PieceColor::black) ? 0 : 7;
        chessboard.grid[rookNewX][rookY] = std::move(chessboard.grid[rookX][rookY]);
        chessboard.grid[rookNewX][rookY]->position = {(float)rookNewX, (float)rookY};
        chessboard.grid[rookNewX][rookY]->moveCount++;
    }
}

void Game::promote(std::shared_ptr<Piece>& piece) {
    int x = piece->position.x;
    int y = piece->position.y;
    chessboard.grid[x][y] = (piece->color == PieceColor::black) ?  Queen::CreateBlack(x, y): chessboard.grid[x][y] = Queen::CreateWhite(x, y);
}

void Game::CalculateLegalMoves() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessboard.grid[i][j] && chessboard.grid[i][j]->color == ColorTurn ) chessboard.grid[i][j]->SetLegalMoves(chessboard.grid);
        }
    }


    bool NoPossibleMoves = std::all_of(&chessboard.grid[0][0], &chessboard.grid[0][0] + 8 * 8, [&](auto& piece) { return !piece || piece->color != ColorTurn || piece->legalMoves.empty(); });
    if (isKingChecked(chessboard.grid)) {
        PlaySound(checkSound);
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