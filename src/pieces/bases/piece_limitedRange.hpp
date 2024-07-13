#pragma once

#include "piece.hpp"

class LimitedRangePiece : public Piece {
   public:
    void SetMoves(std::array<std::shared_ptr<Piece>,64> grid) override;
    bool isAtackingKing(std::array<std::shared_ptr<Piece>,64> grid) override;

   protected:
    LimitedRangePiece(float column, float row, const std::string& pieceName, std::vector<Vector2> moveDirections, PieceColor color) : Piece(column, row, pieceName, color), moveDirections(moveDirections){};
    virtual ~LimitedRangePiece() = default;
    std::vector<Vector2> moveDirections;
};