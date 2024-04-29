#pragma once
#include <raylib.h>
#include <string>

extern int cellSize;

class Piece {
   public:
    Piece(float column, float row, const std::string& pieceName);
    virtual ~Piece();
    Vector2 position;
    Texture2D texture;
    void Draw();
    virtual void Move() = 0;
    virtual int getValue() = 0;
    virtual bool whiteColor() = 0;
};
