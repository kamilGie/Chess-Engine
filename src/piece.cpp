#include "piece.hpp"

Piece::Piece(float column,float row):position(Vector2{row,column}) {}

void Piece::Draw(){
    DrawRectangle(position.x*cellSize,position.y*cellSize,cellSize,cellSize,RED);
}
