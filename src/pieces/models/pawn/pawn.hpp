#pragma once

#include "../../bases/piece.hpp"
class Pawn : public Piece {
    Pawn(float column, float row, const std::string& pieceName, PieceColor color);
   public:
    Vector2 en_passant = {0,0};

    int getValue() override { return 1; }
    void SetMoves(std::array<std::shared_ptr<Piece>,64> grid) override;
    bool isAtackingKing(std::array<std::shared_ptr<Piece>,64> grid) override;
    std::shared_ptr<Piece> clone() override;

    friend class PawnPieceFactory;
};