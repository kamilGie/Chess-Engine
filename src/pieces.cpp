#include "piece_interfaces.hpp"

#define ORTHOGONAL_MOVES \
    {1, 0}, {0, 1}, {-1, 0}, { 0, -1 }
#define DIAGONALLY_MOVES \
    {1, 1}, {1, -1}, {-1, 1}, { -1, -1 }
#define L_SHAPED_MOVES \
    {1, 2}, {2, 1}, {-2, 1}, {1, -2}, {-1, 2}, {2, -1}, {-1, -2}, { -2, -1 }

// ### KING ### //

class King : public LimitedRangePiece {
   public:
    King(float column, float row, const std::string& pieceName) : LimitedRangePiece(column, row, pieceName, {ORTHOGONAL_MOVES, DIAGONALLY_MOVES}){};
    virtual ~King() = default;
    int getValue() override { return 20; }
};

#include <iostream>
class KingBlack : public King {
   public:
    KingBlack(float column=3, float row=0) : King(column, row, "kingBlack") {std::cout<<"ODPALAM SIE "<< column<<" "<<row<<std::endl;}
    bool whiteColor() override { return false; }
};

class KingWhite : public King {
   public:
    KingWhite(float column=3, float row=7) : King(column, row, "kingWhite") {}
    bool whiteColor() override { return true; }
};

// ### QUEEN ### //

class Queen : public LongRangePiece {
   public:
    Queen(float column, float row, const std::string& pieceName) : LongRangePiece(column, row, pieceName, {{ORTHOGONAL_MOVES, DIAGONALLY_MOVES}}){};
    virtual ~Queen() = default;
    int getValue() override { return 10; }
};

class QueenBlack : public Queen {
   public:
    QueenBlack(float column=4, float row=0) : Queen(column, row, "QueenBlack") {}
    bool whiteColor() override { return false; }
};

class QueenWhite : public Queen {
   public:
    QueenWhite(float column=4, float row=7) : Queen(column, row, "QueenWhite") {}
    bool whiteColor() override { return true; }
};

// ### ROOK ### //

class Rook : public LongRangePiece {
   public:
    Rook(float column, float row, const std::string& pieceName) : LongRangePiece(column, row, pieceName, {ORTHOGONAL_MOVES}){};
    virtual ~Rook() = default;
    int getValue() override { return 5; }
};

class RookBlack : public Rook {
   public:
    RookBlack(float column, float row=0) : Rook(column, row, "RookBlack") {}
    bool whiteColor() override { return false; }
};

class RookWhite : public Rook {
   public:
    RookWhite(float column, float row=7) : Rook(column, row, "RookWhite") {}
    bool whiteColor() override { return true; }
};

// ### HORSE ###//

class Horse : public LimitedRangePiece {
   public:
    Horse(float column, float row, const std::string& pieceName) : LimitedRangePiece(column, row, pieceName, {L_SHAPED_MOVES}){};
    virtual ~Horse() = default;
    int getValue() override { return 3; }
};

class HorseBlack : public Horse {
   public:
    HorseBlack(float column, float row=0) : Horse(column, row, "/HorseBlack") {}
    bool whiteColor() override { return false; }
};

class HorseWhite : public Horse {
   public:
    HorseWhite(float column, float row=7) : Horse(column, row, "HorseWhite") {}
    bool whiteColor() override { return true; }
};

// ### BISHOP ### //

class Bishop : public LongRangePiece {
   public:
    Bishop(float column, float row, const std::string& pieceName) : LongRangePiece(column, row, pieceName, {DIAGONALLY_MOVES}){};
    virtual ~Bishop() = default;
    int getValue() override { return 3; }
};

class BishopBlack : public Bishop {
   public:
    BishopBlack(float column, float row=0) : Bishop(column, row, "BishopBlack") {}
    bool whiteColor() override { return false; }
};

class BishopWhite : public Bishop {
   public:
    BishopWhite(float column, float row=7) : Bishop(column, row, "BishopWhite") {}
    bool whiteColor() override { return true; }
};

// ### PAWN ### //

class Pawn : public Piece {
   public:
    Pawn(float column, float row, const std::string& pieceName) : Piece(column, row, pieceName){};
    virtual ~Pawn() = default;
    int getValue() override { return 1; }

    void SetLegalMoves(Piece* grid[][8]) override {
        legalMoves.clear();

        if (position.y == 7 || position.y == 0) return;
        int moveDirection = whiteColor() ? -1 : 1;
        int x = position.x;
        int y = position.y + moveDirection;
        if (!grid[x][y]) {
            addLegalMove(x, y);
            bool isFirstMove = whiteColor() ? 6 == position.y : 1 == position.y;
            if (isFirstMove && !grid[x][y + moveDirection]) addLegalMove(x, y + moveDirection);
        }
        if (x > 0 && grid[x - 1][y] && grid[x - 1][y]->whiteColor() != whiteColor()) addLegalMove(x - 1, y);
        if (x < 7 && grid[x + 1][y] && grid[x + 1][y]->whiteColor() != whiteColor()) addLegalMove(x + 1, y);
    }
};

class PawnBlack : public Pawn {
   public:
    PawnBlack(float column, float row) : Pawn(column, row, "pawnBlack") {}
    bool whiteColor() override { return false; }
};

class PawnWhite : public Pawn {
   public:
    PawnWhite(float column, float row) : Pawn(column, row, "pawnWhite") {}
    bool whiteColor() override { return true; }
};