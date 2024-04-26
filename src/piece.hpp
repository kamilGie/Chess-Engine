#pragma once
#include <raylib.h>


class Piece{
    public:
    Piece(float column,float row);
    Vector2 position;
    int cellSize=100;
    void Draw();

};
