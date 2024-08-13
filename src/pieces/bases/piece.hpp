#pragma once
#include <raylib.h>

#include <memory>
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
    void Draw() const;
    
    virtual int getValue() = 0;
    static PieceFactory& Create();
    virtual void SetMoves(std::array<std::shared_ptr<Piece>,64> grid) = 0;
    virtual bool isAtackingKing(std::array<std::shared_ptr<Piece>,64> grid) = 0;
    bool SafeMove(int x, int y, std::array<std::shared_ptr<Piece>,64> grid);
    virtual std::shared_ptr<Piece> clone() = 0;

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
    bool isKingChecked(std::array<std::shared_ptr<Piece>,64> grid);
};