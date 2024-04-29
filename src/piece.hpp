#pragma once
#include <raylib.h>

extern int cellSize;

class Piece {
   public:
    Piece(float column, float row);
    virtual ~Piece() = default;
    Vector2 position;
    Texture2D texture;
    void Draw();
    virtual void Move() = 0;
    virtual int getValue() = 0;
};
