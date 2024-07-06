#pragma once

#include "../../bases/piece.hpp"
class Pawn : public Piece {
    Pawn(float column, float row, const std::string& pieceName, PieceColor color);
   public:
    Vector2 en_passant = {0,0};

    int getValue() override { return 1; }
    void SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]) override;
    bool SetAtackedPools(std::shared_ptr<Piece> grid[][8], bool atackedPools[8][8]) override;

    friend class PawnPieceFactory;
};