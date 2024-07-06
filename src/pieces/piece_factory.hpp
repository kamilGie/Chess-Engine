#pragma once
#include <memory>

class Piece;
class Pawn;
class Rook;
class Horse;
class Bishop;
class Queen;
class King;

class PieceFactory {
   public:
    PieceFactory& KingBlack();
    PieceFactory& KingWhite();
    PieceFactory& QueenBlack();
    PieceFactory& QueenWhite();
    PieceFactory& BishopBlack();
    PieceFactory& BishopWhite();
    PieceFactory& HorseBlack();
    PieceFactory& HorseWhite();
    PieceFactory& RookBlack();
    PieceFactory& RookWhite();
    PieceFactory& PawnBlack();
    PieceFactory& PawnWhite();

    PieceFactory& Position(int x, int y);

    operator std::shared_ptr<Piece>() const { return std::move(P); }

    static void UnloadTextures();

   private:
    std::shared_ptr<Piece> P;

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
};