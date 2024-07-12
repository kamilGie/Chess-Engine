#pragma once
#include "../../bases/piece_limitedRange.hpp"

class King : public LimitedRangePiece {
    King(float column, float row, const std::string& pieceName, PieceColor color) : LimitedRangePiece(column, row, pieceName, {ORTHOGONAL_MOVES, DIAGONALLY_MOVES}, color){};
   public:
    int getValue() override { return 100; }
    void SetMoves(std::shared_ptr<Piece> (&grid)[][8]) override;
    bool isGettingAtack(std::shared_ptr<Piece> grid[][8]);
    void SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]);

    friend class KingPieceFactory;
};