#include "piece.hpp"


// ### KING ### //

class King : public Piece {
   public:
    King(float column, float row) : Piece(column, row){};
    virtual ~King()=default;
    void Move() override { }
};

class KingBlack : public King {
   public:
    KingBlack(float column, float row) : King(column, row){
        Image image = LoadImage("Graphics/kingBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
};

class KingWhite : public King {
   public:
    KingWhite(float column, float row) : King(column, row){
        Image image = LoadImage("Graphics/kingWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
};


// ### QUEEN ### //

class Queen : public Piece {
   public:
    Queen(float column, float row) : Piece(column, row){};
    virtual ~Queen()=default;
    void Move() override { }
};

class QueenBlack : public Queen {
   public:
    QueenBlack(float column, float row) : Queen(column, row){
        Image image = LoadImage("Graphics/QueenBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
};

class QueenWhite : public Queen {
   public:
    QueenWhite(float column, float row) : Queen(column, row){
        Image image = LoadImage("Graphics/QueenWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
};


// ### ROOK ### //

class Rook : public Piece {
   public:
    Rook(float column, float row) : Piece(column, row){};
    virtual ~Rook()=default;
    void Move() override { }
};

class RookBlack : public Rook {
   public:
    RookBlack(float column, float row) : Rook(column, row){
        Image image = LoadImage("Graphics/RookBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
};

class RookWhite : public Rook {
   public:
    RookWhite(float column, float row) : Rook(column, row){
        Image image = LoadImage("Graphics/RookWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
};


// ### HORSE ###//

class Horse : public Piece {
   public:
    Horse(float column, float row) : Piece(column, row){};
    virtual ~Horse()=default;
    void Move() override { }
};

class HorseBlack : public Horse {
   public:
    HorseBlack(float column, float row) : Horse(column, row){
        Image image = LoadImage("Graphics/HorseBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
};

class HorseWhite : public Horse {
    public:
    HorseWhite(float column, float row) : Horse(column, row){
        Image image = LoadImage("Graphics/HorseWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
};


// ### BISHOP ### //

class Bishop : public Piece {
   public:
    Bishop(float column, float row) : Piece(column, row){};
    virtual ~Bishop()=default;
    void Move() override { }
};

class BishopBlack : public Bishop {
   public:
    BishopBlack(float column, float row) : Bishop(column, row){
        Image image = LoadImage("Graphics/BishopBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
};

class BishopWhite : public Bishop {
   public:
    BishopWhite(float column, float row) : Bishop(column, row){
        Image image = LoadImage("Graphics/BishopWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
};


// ### PAWN ### //

class Pawn : public Piece {
   public:
    Pawn(float column, float row) : Piece(column, row) {};
    virtual ~Pawn()=default;
};

class PawnBlack : public Pawn {
   public:
    PawnBlack(float column, float row) : Pawn(column, row) {
        Image image = LoadImage("Graphics/pawnBlack.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    void Move() override { } 
};

class PawnWhite : public Pawn {
   public:
    PawnWhite(float column, float row) : Pawn(column, row) {
        Image image = LoadImage("Graphics/pawnWhite.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    void Move() override { } 
};