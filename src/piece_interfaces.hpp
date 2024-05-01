#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <array>

extern int cellSize;

class Piece {
   public:
    Piece(float column, float row, const std::string& pieceName);
    virtual ~Piece();
    Vector2 position;
    std::vector <Vector2> legalMoves;
    Texture2D texture;
    void Draw();
    virtual int getValue() = 0;
    virtual bool whiteColor() = 0;
    virtual void SetLegalMoves(Piece* grid[][8])=0;
};


class LongRangePiece : public Piece{
    public:
    LongRangePiece(float column, float row, const std::string& pieceName,std::vector<Vector2> moveDirections) : Piece(column, row, pieceName),moveDirections(moveDirections){};
    virtual ~LongRangePiece()=default;
    std::vector<Vector2> moveDirections;

    void SetLegalMoves(Piece* grid[][8]) override;

};


class LimitedRangePiece : public Piece{ 
    public:
    LimitedRangePiece(float column, float row, const std::string& pieceName,std::vector<Vector2> moveDirections) : Piece(column, row, pieceName),moveDirections(moveDirections){};
    virtual ~LimitedRangePiece()=default;
    std::vector<Vector2> moveDirections;
    void SetLegalMoves(Piece* grid[][8]) override;
};


bool isInBorder(int x ,int y);