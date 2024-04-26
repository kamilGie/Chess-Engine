#include "piece.hpp"

class Horse : public Piece {
   public:
    Horse(float column, float row,Color color) : Piece(column, row, color){};
    void Move() override {

    }

    void Draw() override {
        DrawText("Horse",position.x*cellSize,position.y*cellSize,20,color);
    }

};

class Pawn : public Piece {
   public:
    Pawn(float column, float row,Color color) : Piece(column, row, color){};
    void Move() override {

    }

    void Draw() override {
        DrawText("pawn",position.x*cellSize,position.y*cellSize,20,color);
    }

};

class Rook : public Piece {
   public:
    Rook(float column, float row,Color color) : Piece(column, row, color){};
    void Move() override {

    }

    void Draw() override {
        DrawText("Rook",position.x*cellSize,position.y*cellSize,20,color);
    }

};

class Bishop : public Piece {
   public:
    Bishop(float column, float row,Color color) : Piece(column, row, color){};
    void Move() override {

    }

    void Draw() override {
        DrawText("Bishop",position.x*cellSize,position.y*cellSize,20,color);
    }

};

class Queen : public Piece {
   public:
    Queen(float column, float row,Color color) : Piece(column, row, color){};
    void Move() override {

    }

    void Draw() override {
        DrawText("Queen",position.x*cellSize,position.y*cellSize,20,color);
    }

};

class King : public Piece {
   public:
    King(float column, float row,Color color) : Piece(column, row, color){};
    void Move() override {

    }

    void Draw() override {
        DrawText("King",position.x*cellSize,position.y*cellSize,20,color);
    }

};