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
    virtual void Move() = 0;
    virtual int getValue() = 0;
    virtual bool whiteColor() = 0;
    virtual void SetLegalMoves(Piece* grid[][8])=0;
};
