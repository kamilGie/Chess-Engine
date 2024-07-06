#pragma once
#include "../../bases/piece_limitedRange.hpp"

class Horse : public LimitedRangePiece {
    Horse(float column, float row, const std::string& pieceName, PieceColor color) : LimitedRangePiece(column, row, pieceName, {L_SHAPED_MOVES}, color){};
   public:
    int getValue() override { return 3; }

    friend class HorsePieceFactory;
};