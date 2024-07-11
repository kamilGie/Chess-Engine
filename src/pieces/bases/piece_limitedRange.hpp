#pragma once

#include "piece.hpp"

class LimitedRangePiece : public Piece {
   public:
    void SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]) override;
    bool isAtackingKing(std::shared_ptr<Piece> grid[][8]) override;

   protected:
    LimitedRangePiece(float column, float row, const std::string& pieceName, std::vector<Vector2> moveDirections, PieceColor color) : Piece(column, row, pieceName, color), moveDirections(moveDirections){};
    virtual ~LimitedRangePiece() = default;
    std::vector<Vector2> moveDirections;
};