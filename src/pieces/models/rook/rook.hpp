#pragma once
#include "../../bases/piece_longRange.hpp"

class Rook : public LongRangePiece {
    Rook(float column, float row, const std::string& pieceName, PieceColor color) : LongRangePiece(column, row, pieceName, {ORTHOGONAL_MOVES}, color){};   public:
    int getValue() override { return 5; }

    friend class RookPieceFactory;
};