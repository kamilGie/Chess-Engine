#pragma once

#include "piece_interfaces.hpp"

class King : public LimitedRangePiece {
   public:
    King(float column, float row, const std::string& pieceName, PieceColor color);
    virtual ~King() = default;
    int getValue() override { return 20; }
    void SetLegalMoves(std::shared_ptr<Piece> grid[][8]) override;

    static std::shared_ptr<King> CreateBlack(float column, float row);
    static std::shared_ptr<King> CreateWhite(float column, float row);
};


class Queen : public LongRangePiece {
   public:
    Queen(float column, float row, const std::string& pieceName, PieceColor color);
    virtual ~Queen() = default;
    int getValue() override { return 10; }

    static std::shared_ptr<Queen> CreateBlack(float column, float row);
    static std::shared_ptr<Queen> CreateWhite(float column, float row);
};

class Rook : public LongRangePiece {
   public:
    Rook(float column, float row, const std::string& pieceName, PieceColor color);
    virtual ~Rook() = default;
    int getValue() override { return 5; }

    static std::shared_ptr<Rook> CreateBlack(float column, float row);
    static std::shared_ptr<Rook> CreateWhite(float column, float row);
};


class Horse : public LimitedRangePiece {
   public:
    Horse(float column, float row, const std::string& pieceName, PieceColor color);
    virtual ~Horse() = default;
    int getValue() override { return 3; }

    static std::shared_ptr<Horse> CreateBlack(float column, float row);
    static std::shared_ptr<Horse> CreateWhite(float column, float row);
};

class Bishop : public LongRangePiece {
   public:
    Bishop(float column, float row, const std::string& pieceName, PieceColor color);
    virtual ~Bishop() = default;
    int getValue() override { return 3; }

    static std::shared_ptr<Bishop> CreateBlack(float column, float row);
    static std::shared_ptr<Bishop> CreateWhite(float column, float row);
};

class Pawn : public Piece {
   public:
    Pawn(float column, float row, const std::string& pieceName, PieceColor color);
    virtual ~Pawn() = default;
    int getValue() override { return 1; }

    Vector2 en_passant = {0,0};

    void SetLegalMoves(std::shared_ptr<Piece> grid[][8]) override;
    bool SetAtackedPools(std::shared_ptr<Piece> grid[][8], bool atackedPools[8][8]) override;

    static std::shared_ptr<Pawn> CreateBlack(float column, float row);
    static std::shared_ptr<Pawn> CreateWhite(float column, float row);
};