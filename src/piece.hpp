#pragma once
#include <raylib.h>


class Piece{
    public:
    Piece(float column,float row);
    ~Piece();
    Vector2 position;
    Texture2D texture;
    int cellSize=100;
    void Draw();
    virtual void Move()=0;
};
