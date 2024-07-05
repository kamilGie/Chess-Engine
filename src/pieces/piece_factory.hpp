#pragma once
#include <raylib.h>

#include <memory>
#include <unordered_map>

#include "pieces.hpp"

class PieceFactory {
   public:
    static std::shared_ptr<Pawn> BlackPawn(int x, int y);
    static std::shared_ptr<Pawn> WhitePawn(int x, int y);
    static std::shared_ptr<Rook> BlackRook(int x, int y);
    static std::shared_ptr<Rook> WhiteRook(int x, int y);
    static std::shared_ptr<Horse> BlackHorse(int x, int y);
    static std::shared_ptr<Horse> WhiteHorse(int x, int y);
    static std::shared_ptr<Bishop> BlackBishop(int x, int y);
    static std::shared_ptr<Bishop> WhiteBishop(int x, int y);
    static std::shared_ptr<Queen> BlackQueen(int x, int y);
    static std::shared_ptr<Queen> WhiteQueen(int x, int y);
    static std::shared_ptr<King> BlackKing(int x, int y);
    static std::shared_ptr<King> WhiteKing(int x, int y);

    static void UnloadTextures();

   private:
    static Pawn GetWhitePawnPrototype();
    static Pawn GetBlackPawnPrototype();
    static Rook GetWhiteRookPrototype();
    static Rook GetBlackRookPrototype();
    static Horse GetWhiteHorsePrototype();
    static Horse GetBlackHorsePrototype();
    static Bishop GetWhiteBishopPrototype();
    static Bishop GetBlackBishopPrototype();
    static Queen GetWhiteQueenPrototype();
    static Queen GetBlackQueenPrototype();
    static King GetWhiteKingPrototype();
    static King GetBlackKingPrototype();

    PieceFactory() = delete;
};