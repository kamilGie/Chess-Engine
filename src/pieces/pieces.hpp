#pragma once

#include "piece_interfaces.hpp"

class King : public LimitedRangePiece {
    King(float column, float row, const std::string& pieceName, PieceColor color);
   public:
    int getValue() override { return 20; }
    void SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]) override;

    friend class PieceFactory;
};


class Queen : public LongRangePiece {
    Queen(float column, float row, const std::string& pieceName, PieceColor color);
   public:
    int getValue() override { return 10; }

    friend class PieceFactory;
};

class Rook : public LongRangePiece {
    Rook(float column, float row, const std::string& pieceName, PieceColor color);
   public:
    int getValue() override { return 5; }

    friend class PieceFactory;
};


class Horse : public LimitedRangePiece {
    Horse(float column, float row, const std::string& pieceName, PieceColor color);
   public:
    int getValue() override { return 3; }

    friend class PieceFactory;
};

class Bishop : public LongRangePiece {
    Bishop(float column, float row, const std::string& pieceName, PieceColor color);
   public:
    int getValue() override { return 3; }

    friend class PieceFactory;
};

class Pawn : public Piece {
    Pawn(float column, float row, const std::string& pieceName, PieceColor color);
   public:
    Vector2 en_passant = {0,0};

    int getValue() override { return 1; }
    void SetLegalMoves(std::shared_ptr<Piece> (&grid)[][8]) override;
    bool SetAtackedPools(std::shared_ptr<Piece> grid[][8], bool atackedPools[8][8]) override;

    friend class PieceFactory;
};