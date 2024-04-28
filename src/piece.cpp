#include "piece.hpp"

Piece::Piece(float column,float row):position(Vector2{row,column}) {}

void Piece::Draw(){ DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE); }
