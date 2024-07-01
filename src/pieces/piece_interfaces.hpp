#pragma once
#include <raylib.h>

#include <string>
#include <vector>
#include <memory>
#include <iostream>

enum class PieceColor{
    black,
    white
};


extern int cellSize;

class Piece {
   public:
    Piece(float column, float row, const std::string& pieceName, PieceColor color);
    virtual ~Piece();

    void Draw();
    virtual int getValue() = 0;
    virtual void SetLegalMoves(std::shared_ptr<Piece> grid[][8]) = 0;
    virtual bool SetAtackedPools(std::shared_ptr<Piece> grid[][8],bool atackedPools[8][8]) = 0;

    Vector2 position;
    PieceColor color;
    int moveCount = 0;
    Texture2D texture;
    std::vector<Vector2> legalMoves;

   protected:
    void addLegalMove(int x, int y);
    bool isInsideBoard(int x, int y);
    bool isKingChecked(std::shared_ptr<Piece> grid[][8]);
    bool SafeMove(int x, int y, std::shared_ptr<Piece> grid[][8]);

};

class LongRangePiece : public Piece {
   public:
    LongRangePiece(float column, float row, const std::string& pieceName, std::vector<Vector2> moveDirections,PieceColor color) : Piece(column, row, pieceName,color), moveDirections(moveDirections){};
    virtual ~LongRangePiece() = default;
    void SetLegalMoves(std::shared_ptr<Piece> grid[][8]) override;
    bool SetAtackedPools(std::shared_ptr<Piece> grid[][8],bool atackedPools[8][8]) override;

   protected:
    std::vector<Vector2> moveDirections;
};

class LimitedRangePiece : public Piece {
   public:
    LimitedRangePiece(float column, float row, const std::string& pieceName, std::vector<Vector2> moveDirections,PieceColor color) : Piece(column, row, pieceName,color), moveDirections(moveDirections){};
    virtual ~LimitedRangePiece() = default;
    void SetLegalMoves(std::shared_ptr<Piece> grid[][8]) override;
    bool SetAtackedPools(std::shared_ptr<Piece> grid[][8],bool atackedPools[8][8]) override;

   protected:
    std::vector<Vector2> moveDirections;
};
