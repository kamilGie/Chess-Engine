#pragma once
#include "../../bases/piece_limitedRange.hpp"

class King : public LimitedRangePiece {
    King(float column, float row, const std::string& pieceName, PieceColor color) : LimitedRangePiece(column, row, pieceName, {ORTHOGONAL_MOVES, DIAGONALLY_MOVES}, color){};
   public:
    int getValue() override { return 100; }
    void SetMoves(std::array<std::shared_ptr<Piece>,64> grid) override;
    bool isGettingAtack(std::array<std::shared_ptr<Piece>,64> grid);
    void SetLegalMoves(std::array<std::shared_ptr<Piece>,64> grid);

    friend class KingPieceFactory;
};