#pragma once

#include <raylib.h>
#include <iostream>
#include "chessboard.hpp"
#include "piece.hpp"
#include "pieces.cpp"

class Game {
   public:
    Chessboard chessboard = Chessboard();

    QueenBlack queenBlack = QueenBlack(0,4);
    QueenWhite queenWhite = QueenWhite(7,4);

    KingBlack kingBlack = KingBlack(0,3);
    KingWhite kingWhite = KingWhite(7,3);

    RookBlack rookBlackA = RookBlack(0,0);
    RookBlack rookBlackH = RookBlack(0,7);
    RookWhite rookWhiteA = RookWhite(7,0);
    RookWhite rookWhiteH = RookWhite(7,7);

    HorseBlack horseBlackB = HorseBlack(0,1);
    HorseBlack horseBlackG = HorseBlack(0,6);
    HorseWhite horseWhiteB = HorseWhite(7,1);
    HorseWhite horseWhiteG = HorseWhite(7,6);

    BishopBlack bishopBlackC = BishopBlack(0,2);
    BishopBlack bishopBlackF = BishopBlack(0,5);
    BishopWhite bishopWhiteC = BishopWhite(7,2);
    BishopWhite bishopWhiteF = BishopWhite(7,5);

    PawnBlack PawnBlackA = PawnBlack(1,0);
    PawnBlack PawnBlackB = PawnBlack(1,1);
    PawnBlack PawnBlackC = PawnBlack(1,2);
    PawnBlack PawnBlackD = PawnBlack(1,3);
    PawnBlack PawnBlackE = PawnBlack(1,4);
    PawnBlack PawnBlackF = PawnBlack(1,5);
    PawnBlack PawnBlackG = PawnBlack(1,6);
    PawnBlack PawnBlackH = PawnBlack(1,7);

    PawnWhite PawnWhiteA = PawnWhite(6,0);
    PawnWhite PawnWhiteB = PawnWhite(6,1);
    PawnWhite PawnWhiteC = PawnWhite(6,2);
    PawnWhite PawnWhiteD = PawnWhite(6,3);
    PawnWhite PawnWhiteE = PawnWhite(6,4);
    PawnWhite PawnWhiteF = PawnWhite(6,5);
    PawnWhite PawnWhiteG = PawnWhite(6,6);
    PawnWhite PawnWhiteH = PawnWhite(6,7);

    void Draw();
};