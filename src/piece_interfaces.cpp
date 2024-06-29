#include "piece_interfaces.hpp"

Piece::Piece(float column, float row, const std::string& pieceName, PieceColor color) : position(Vector2{column, row}) , color(color) {
    std::string fullPath = "Graphics/" + pieceName + ".png";
    Image image = LoadImage(fullPath.c_str());
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Piece::~Piece() { UnloadTexture(texture); }

void Piece::Draw() { DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE); }

bool Piece::isInsideBoard(int x, int y) { return x < 8 && y < 8 && x >= 0 && y >= 0; }



void Piece::addLegalMove(int x, int y) { legalMoves.push_back({static_cast<float>(x), static_cast<float>(y)});  }

bool Piece::SafeMove(int x, int y, std::shared_ptr<Piece> grid[][8]) {
    bool res=true;
    std::shared_ptr<Piece> tempCaptured = grid[x][y];
    grid[x][y] = std::move(grid[(int)position.x][(int)position.y]);
    Vector2 BeforeMove = position;
    grid[(int)position.x][(int)position.y] = nullptr;
    position = {static_cast<float>(x), static_cast<float>(y)};

    bool AtackedPools[8][8]{};
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++){
            if(grid[i][j] && grid[i][j]->color != color) grid[i][j]->SetAtackedPools(grid,AtackedPools);
        }
    }
    std::shared_ptr<Piece> king = nullptr;
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++){
            if(grid[i][j] && grid[i][j]->color == color && grid[i][j]->getValue() == 20){
                 king = grid[i][j];
                 break;
            }
        }
    }
    if(AtackedPools[(int)king->position.x][(int)king->position.y]) res = false;

    // Restore the original position of the moved piece
    position = BeforeMove;
    grid[(int)BeforeMove.x][(int)BeforeMove.y] = std::move(grid[x][y]);
    grid[x][y] = tempCaptured;

    return res;
}

void LongRangePiece::SetLegalMoves(std::shared_ptr<Piece> grid[][8]) {
    legalMoves.clear();

    for (Vector2 dir : moveDirections) {
        int x = position.x;
        int y = position.y;
        do {
            x += dir.x;
            y += dir.y;
            bool isEmptyOrOpponent = isInsideBoard(x, y) && (!grid[x][y] || grid[x][y]->color != color);
            if (isEmptyOrOpponent && SafeMove(x,y,grid)) addLegalMove(x, y);
        } while (!grid[x][y]);
    }
}

void LimitedRangePiece::SetAtackedPools(std::shared_ptr<Piece> grid[][8],bool atackedPools[8][8]) {
    for (Vector2 dir : moveDirections) {
        int x = position.x + dir.x;
        int y = position.y + dir.y;
        if (isInsideBoard(x, y)) atackedPools[x][y] = true;
    }
}

void LimitedRangePiece::SetLegalMoves(std::shared_ptr<Piece> grid[][8]) {
    legalMoves.clear();
    for (Vector2 dir : moveDirections) {
        int x = position.x + dir.x;
        int y = position.y + dir.y;
        bool isEmptyOrOpponent = isInsideBoard(x, y) && (!grid[x][y] || grid[x][y]->color != color);
        if (isEmptyOrOpponent && SafeMove(x,y,grid)) addLegalMove(x, y);
    }
}

void LongRangePiece::SetAtackedPools(std::shared_ptr<Piece> grid[][8],bool atackedPools[8][8]) {
    for (Vector2 dir : moveDirections) {
        int x = position.x;
        int y = position.y;
        do {
            x += dir.x;
            y += dir.y;
            if (isInsideBoard(x, y)) atackedPools[x][y] = true;
        } while (!grid[x][y]);
    }
}