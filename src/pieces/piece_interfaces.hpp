#pragma once
#include <raylib.h>

#include <memory>
#include <string>
#include <vector>
#include "piece_factory.hpp"

enum class PieceColor {
    black,
    white
};

class PieceFactory;

extern int cellSize;

class Piece {
   public:
    void Draw();
    // to set creating piece type do .(name of the piece).posttion(x,y);
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

class LongRangePiece : public Piece {
   public:
    void SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]) override;
    bool SetAtackedPools(std::shared_ptr<Piece> grid[][8], bool atackedPools[8][8]) override;

   protected:
    LongRangePiece(float column, float row, const std::string& pieceName, std::vector<Vector2> moveDirections, PieceColor color) : Piece(column, row, pieceName, color), moveDirections(moveDirections){};
    virtual ~LongRangePiece() = default;
    std::vector<Vector2> moveDirections;
};

class LimitedRangePiece : public Piece {
   public:
    void SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]) override;
    bool SetAtackedPools(std::shared_ptr<Piece> grid[][8], bool atackedPools[8][8]) override;

   protected:
    LimitedRangePiece(float column, float row, const std::string& pieceName, std::vector<Vector2> moveDirections, PieceColor color) : Piece(column, row, pieceName, color), moveDirections(moveDirections){};
    virtual ~LimitedRangePiece() = default;
    std::vector<Vector2> moveDirections;
};
