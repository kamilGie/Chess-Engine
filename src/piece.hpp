#pragma once
#include <raylib.h>


class Piece{
    public:
    Piece(float column,float row,Color color);
    virtual ~Piece()=default;
    Vector2 position;
    int cellSize=100;
    virtual void Draw()=0;
    virtual void Move()=0;
    Color color;
};
