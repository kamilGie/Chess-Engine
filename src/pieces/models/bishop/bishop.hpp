#pragma once    

#include "../../bases/piece_longRange.hpp"

class Bishop : public LongRangePiece {
    Bishop(float column, float row, const std::string& pieceName, PieceColor color) : LongRangePiece(column, row, pieceName, {DIAGONALLY_MOVES}, color){};

   public:
    int getValue() override { return 3; }

    friend class BishopPieceFactory;
};