#pragma once
#include <raylib.h>

#include <memory>
#include <string>
#include <vector>

#define ORTHOGONAL_MOVES \
    {1, 0}, {0, 1}, {-1, 0}, { 0, -1 }
#define DIAGONALLY_MOVES \
    {1, 1}, {1, -1}, {-1, 1}, { -1, -1 }
#define L_SHAPED_MOVES \
    {1, 2}, {2, 1}, {-2, 1}, {1, -2}, {-1, 2}, {2, -1}, {-1, -2}, { -2, -1 }

enum class PieceColor {
    black,
    white
};

class PieceFactory;

extern int cellSize;

class Piece {
   public:
    void Draw();
    
    static PieceFactory Create();
    virtual int getValue() = 0;
    virtual void SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]) = 0;
    virtual bool SetAtackedPools(std::shared_ptr<Piece> grid[][8], bool atackedPools[8][8]) = 0;

    Vector2 position;
    PieceColor color;
    int moveCount = 0;
    Texture2D texture;
    std::vector<Vector2> legalMoves = {};

   protected:
    Piece(float column, float row, const std::string& pieceName, PieceColor color);
    virtual ~Piece() = default;
    void addLegalMove(int x, int y);
    bool isInsideBoard(int x, int y);
    bool isKingChecked(std::shared_ptr<Piece> grid[][8]);
    bool SafeMove(int x, int y, std::shared_ptr<Piece> grid[][8]);
};