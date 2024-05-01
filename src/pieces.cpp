#include "piece_interfaces.hpp"

#define ORTHOGONAL_MOVES {1, 0}, {0, 1}, {-1, 0}, {0, -1}
#define DIAGONALLY_MOVES {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
extern int cellSize;

// ### KING ### //

class King : public Piece {
   public:
    King(float column, float row, const std::string& pieceName) : Piece(column, row, pieceName){};
    virtual ~King() = default;
    void Move() override {}
    int getValue() override { return 20; }
    std::array<Vector2, 8> PossibleMoves{{ORTHOGONAL_MOVES, DIAGONALLY_MOVES}};

    void SetLegalMoves(Piece* grid[][8]) override {
        legalMoves.clear();

        for (Vector2 move : PossibleMoves) {
            if (position.x + move.x >= 0 && position.x + move.x < 8 && position.y + move.y >= 0 && position.y + move.y < 8 && (!grid[(int)position.x + (int)move.x][(int)position.y + (int)move.y] || grid[(int)position.x + (int)move.x][(int)position.y + (int)move.y]->whiteColor() != whiteColor())) {
                legalMoves.push_back(Vector2Add(move, position));
            }
        }
    }
};

class KingBlack : public King {
   public:
    KingBlack(float column, float row) : King(column, row, "kingBlack") {}
    bool whiteColor() override { return false; }
};

class KingWhite : public King {
   public:
    KingWhite(float column, float row) : King(column, row, "kingWhite") {}
    bool whiteColor() override { return true; }
};

// ### QUEEN ### //

class Queen : public LongRangePiece {
   public:
    Queen(float column, float row, const std::string& pieceName) : LongRangePiece(column, row, pieceName,{{ORTHOGONAL_MOVES, DIAGONALLY_MOVES}}){};
    virtual ~Queen() = default;
    void Move() override {}
    int getValue() override { return 10; }
};

class QueenBlack : public Queen {
   public:
    QueenBlack(float column, float row) : Queen(column, row, "QueenBlack") {}
    bool whiteColor() override { return false; }
};

class QueenWhite : public Queen {
   public:
    QueenWhite(float column, float row) : Queen(column, row, "QueenWhite") {}
    bool whiteColor() override { return true; }
};

// ### ROOK ### //

class Rook : public LongRangePiece {
   public:
    Rook(float column, float row, const std::string& pieceName) : LongRangePiece(column, row, pieceName,{ORTHOGONAL_MOVES}){};
    virtual ~Rook() = default;
    void Move() override {}
    int getValue() override { return 5; }
};

class RookBlack : public Rook {
   public:
    RookBlack(float column, float row) : Rook(column, row, "RookBlack") {}
    bool whiteColor() override { return false; }
};

class RookWhite : public Rook {
   public:
    RookWhite(float column, float row) : Rook(column, row, "RookWhite") {}
    bool whiteColor() override { return true; }
};

// ### HORSE ###//

class Horse : public Piece {
   public:
    Horse(float column, float row, const std::string& pieceName) : Piece(column, row, pieceName){};
    virtual ~Horse() = default;
    void Move() override {}
    int getValue() override { return 3; }
    std::array<Vector2, 8> PossibleMoves{{{1, 2}, {2, 1}, {-2, 1}, {1, -2}, {-1, 2}, {2, -1}, {-1, -2}, {-2, -1}}};

    void SetLegalMoves(Piece* grid[][8]) override {
        legalMoves.clear();

        for (Vector2 move : PossibleMoves) {
            if (position.x + move.x >= 0 && position.x + move.x < 8 && position.y + move.y >= 0 && position.y + move.y < 8 && (!grid[(int)position.x + (int)move.x][(int)position.y + (int)move.y] || grid[(int)position.x + (int)move.x][(int)position.y + (int)move.y]->whiteColor() != whiteColor())) {
                legalMoves.push_back(Vector2Add(move, position));
            }
        }
    }
};

class HorseBlack : public Horse {
   public:
    HorseBlack(float column, float row) : Horse(column, row, "/HorseBlack") {}
    bool whiteColor() override { return false; }
};

class HorseWhite : public Horse {
   public:
    HorseWhite(float column, float row) : Horse(column, row, "HorseWhite") {}
    bool whiteColor() override { return true; }
};

// ### BISHOP ### //

class Bishop : public LongRangePiece {
   public:
    Bishop(float column, float row, const std::string& pieceName) : LongRangePiece(column, row, pieceName,{DIAGONALLY_MOVES}){};
    virtual ~Bishop() = default;
    void Move() override {}
    int getValue() override { return 3; }
};

class BishopBlack : public Bishop {
   public:
    BishopBlack(float column, float row) : Bishop(column, row, "BishopBlack") {}
    bool whiteColor() override { return false; }
};

class BishopWhite : public Bishop {
   public:
    BishopWhite(float column, float row) : Bishop(column, row, "BishopWhite") {}
    bool whiteColor() override { return true; }
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
    bool whiteColor() override { return false; }
    void SetLegalMoves(Piece* grid[][8]) override {
        legalMoves.clear();
        if (position.y == 7) return;

        if (!grid[(int)position.x][(int)position.y + 1]) {
            legalMoves.push_back({position.x, position.y + 1});
            if (position.y == 1 && !grid[(int)position.x][(int)position.y + 2]) {
                legalMoves.push_back({position.x, position.y + 2});
            }
        }

        if (position.x > 0 && grid[(int)position.x - 1][(int)position.y + 1] && grid[(int)position.x - 1][(int)position.y + 1]->whiteColor()) {
            legalMoves.push_back({position.x - 1, position.y + 1});
        }
        if (position.x < 7 && grid[(int)position.x + 1][(int)position.y + 1] && grid[(int)position.x + 1][(int)position.y + 1]->whiteColor()) {
            legalMoves.push_back({position.x + 1, position.y + 1});
        }
    }
};

class PawnWhite : public Pawn {
   public:
    PawnWhite(float column, float row) : Pawn(column, row, "pawnWhite") {}
    void Move() override {}
    bool whiteColor() override { return true; }
    void SetLegalMoves(Piece* grid[][8]) override {
        legalMoves.clear();
        if (position.y == 0) return;

        if (!grid[(int)position.x][(int)position.y - 1]) {
            legalMoves.push_back({position.x, position.y - 1});
            if (position.y == 6 && !grid[(int)position.x][(int)position.y - 2]) {
                legalMoves.push_back({position.x, position.y - 2});
            }
        }
        if (position.x > 0 && grid[(int)position.x - 1][(int)position.y - 1] && !grid[(int)position.x - 1][(int)position.y - 1]->whiteColor()) {
            legalMoves.push_back({position.x - 1, position.y - 1});
        }
        if (position.x < 7 && grid[(int)position.x + 1][(int)position.y - 1] && !grid[(int)position.x + 1][(int)position.y - 1]->whiteColor()) {
            legalMoves.push_back({position.x + 1, position.y - 1});
        }
    }
};