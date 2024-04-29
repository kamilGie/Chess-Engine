#include "piece.hpp"

extern int cellSize;

// ### KING ### //

class King : public Piece {
   public:
    King(float column, float row, const std::string& pieceName) : Piece(column, row, pieceName){};
    virtual ~King() = default;
    void Move() override {}
    int getValue() override { return 20; }
};

class KingBlack : public King {
   public:
    KingBlack(float column, float row) : King(column, row, "kingBlack") {}
    bool whiteColor() override {return false;}
};

class KingWhite : public King {
   public:
    KingWhite(float column, float row) : King(column, row, "kingWhite") {}
    bool whiteColor() override {return true;}
};

// ### QUEEN ### //

class Queen : public Piece {
   public:
    Queen(float column, float row, const std::string& pieceName) : Piece(column, row, pieceName){};
    virtual ~Queen() = default;
    void Move() override {}
    int getValue() override { return 10; }
};

class QueenBlack : public Queen {
   public:
    QueenBlack(float column, float row) : Queen(column, row, "QueenBlack") {}
    bool whiteColor() override {return false;}
};

class QueenWhite : public Queen {
   public:
    QueenWhite(float column, float row) : Queen(column, row, "QueenWhite") {}
    bool whiteColor() override {return true;}
};

// ### ROOK ### //

class Rook : public Piece {
   public:
    Rook(float column, float row, const std::string& pieceName) : Piece(column, row, pieceName){};
    virtual ~Rook() = default;
    void Move() override {}
    int getValue() override { return 5; }
};

class RookBlack : public Rook {
   public:
    RookBlack(float column, float row) : Rook(column, row, "RookBlack") {}
    bool whiteColor() override {return false;}
};

class RookWhite : public Rook {
   public:
    RookWhite(float column, float row) : Rook(column, row, "RookWhite") {}
    bool whiteColor() override {return true;}
};

// ### HORSE ###//

class Horse : public Piece {
   public:
    Horse(float column, float row, const std::string& pieceName) : Piece(column, row, pieceName){};
    virtual ~Horse() = default;
    void Move() override {}
    int getValue() override { return 3; }
};

class HorseBlack : public Horse {
   public:
    HorseBlack(float column, float row) : Horse(column, row, "/HorseBlack") {}
    bool whiteColor() override {return false;}
};

class HorseWhite : public Horse {
   public:
    HorseWhite(float column, float row) : Horse(column, row, "HorseWhite") {}
    bool whiteColor() override {return true;}
};

// ### BISHOP ### //

class Bishop : public Piece {
   public:
    Bishop(float column, float row, const std::string& pieceName) : Piece(column, row, pieceName){};
    virtual ~Bishop() = default;
    void Move() override {}
    int getValue() override { return 3; }
};

class BishopBlack : public Bishop {
   public:
    BishopBlack(float column, float row) : Bishop(column, row, "BishopBlack") {}
    bool whiteColor() override {return false;}
};

class BishopWhite : public Bishop {
   public:
    BishopWhite(float column, float row) : Bishop(column, row, "BishopWhite") {}
    bool whiteColor() override {return true;}
};

// ### PAWN ### //

class Pawn : public Piece {
   public:
    Pawn(float column, float row, const std::string& pieceName) : Piece(column, row, pieceName){};
    virtual ~Pawn() = default;
    int getValue() override { return 1; }
};

class PawnBlack : public Pawn {
   public:
    PawnBlack(float column, float row) : Pawn(column, row, "pawnBlack") {}
    void Move() override {}
    bool whiteColor() override {return false;}
};

class PawnWhite : public Pawn {
   public:
    PawnWhite(float column, float row) : Pawn(column, row, "pawnWhite") {}
    void Move() override {}
    bool whiteColor() override {return true;}
};