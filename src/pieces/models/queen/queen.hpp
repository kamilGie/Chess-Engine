#pragma once
#include "../../bases/piece_longRange.hpp"

class Queen : public LongRangePiece {
    Queen(float column, float row, const std::string& pieceName, PieceColor color) : LongRangePiece(column, row, pieceName, {{ORTHOGONAL_MOVES, DIAGONALLY_MOVES}}, color){};
   public:
    int getValue() override { return 10; }
    std::shared_ptr<Piece> clone() override;

    friend class QueenPieceFactory;
};