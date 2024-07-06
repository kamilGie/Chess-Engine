#pragma once
#include <memory>

class Piece;
class Pawn;
class Rook;
class Horse;
class Bishop;
class Queen;
class King;


class PieceFactoryBase {
   public:
    virtual ~PieceFactoryBase() = default;
    virtual PieceFactoryBase& black() = 0;
    virtual PieceFactoryBase& white() = 0;
    virtual PieceFactoryBase& Position(int x, int y);
    operator std::shared_ptr<Piece>() const { return std::move(P); }

   protected:
    std::shared_ptr<Piece> P;
};

class KingPieceFactory : public PieceFactoryBase {
   public:
    PieceFactoryBase& black() override;
    PieceFactoryBase& white() override;

   private:
    static King GetWhiteKingPrototype();
    static King GetBlackKingPrototype();
};

class QueenPieceFactory : public PieceFactoryBase {
   public:
    PieceFactoryBase& black() override;
    PieceFactoryBase& white() override;

   private:
    static Queen GetWhiteQueenPrototype();
    static Queen GetBlackQueenPrototype();
};

class RookPieceFactory : public PieceFactoryBase {
   public:
    PieceFactoryBase& black() override;
    PieceFactoryBase& white() override;

   private:
    static Rook GetWhiteRookPrototype();
    static Rook GetBlackRookPrototype();
};

class HorsePieceFactory : public PieceFactoryBase {
   public:
    PieceFactoryBase& black() override;
    PieceFactoryBase& white() override;

   private:
    static Horse GetWhiteHorsePrototype();
    static Horse GetBlackHorsePrototype();
};

class BishopPieceFactory : public PieceFactoryBase {
   public:
    PieceFactoryBase& black() override;
    PieceFactoryBase& white() override;

   private:
    static Bishop GetWhiteBishopPrototype();
    static Bishop GetBlackBishopPrototype();
};

class PawnPieceFactory : public PieceFactoryBase {
   public:
    PieceFactoryBase& black() override;
    PieceFactoryBase& white() override;

   private:
    static Pawn GetWhitePawnPrototype();
    static Pawn GetBlackPawnPrototype();
};