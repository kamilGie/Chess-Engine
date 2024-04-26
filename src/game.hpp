#pragma once

#include <raylib.h>
#include <iostream>
#include "chessboard.hpp"
#include "piece.hpp"
#include "pieces.cpp"

class Game {
   public:
    Chessboard chessboard = Chessboard();

    Rook rookBlackA = Rook(0,0,BLACK);
    Rook rookBlackH = Rook(0,7,BLACK);
    Rook rookWhiteA = Rook(7,0,WHITE);
    Rook rookWhiteH = Rook(7,7,WHITE);

    Horse horseBlackB = Horse(0,1,BLACK);
    Horse horseBlackG = Horse(0,6,BLACK);
    Horse horseWhiteB = Horse(7,1,WHITE);
    Horse horseWhiteG = Horse(7,6,WHITE);

    Bishop bishopBlackC = Bishop(0,2,BLACK);
    Bishop bishopBlackF = Bishop(0,5,BLACK);
    Bishop bishopWhiteC = Bishop(7,2,WHITE);
    Bishop bishopWhiteF = Bishop(7,5,WHITE);

    Queen queenBlack = Queen(0,4,BLACK);
    Queen queenWhite = Queen(7,4,WHITE);

    King kingBlack = King(0,3,BLACK);
    King kingWhite = King(7,3,WHITE);

    Pawn PawnBlackA = Pawn(1,0,BLACK);
    Pawn PawnBlackB = Pawn(1,1,BLACK);
    Pawn PawnBlackC = Pawn(1,2,BLACK);
    Pawn PawnBlackD = Pawn(1,3,BLACK);
    Pawn PawnBlackE = Pawn(1,4,BLACK);
    Pawn PawnBlackF = Pawn(1,5,BLACK);
    Pawn PawnBlackG = Pawn(1,6,BLACK);
    Pawn PawnBlackH = Pawn(1,7,BLACK);

    Pawn PawnWhiteA = Pawn(6,0,WHITE);
    Pawn PawnWhiteB = Pawn(6,1,WHITE);
    Pawn PawnWhiteC = Pawn(6,2,WHITE);
    Pawn PawnWhiteD = Pawn(6,3,WHITE);
    Pawn PawnWhiteE = Pawn(6,4,WHITE);
    Pawn PawnWhiteF = Pawn(6,5,WHITE);
    Pawn PawnWhiteG = Pawn(6,6,WHITE);
    Pawn PawnWhiteH = Pawn(6,7,WHITE);

    void Draw();
};