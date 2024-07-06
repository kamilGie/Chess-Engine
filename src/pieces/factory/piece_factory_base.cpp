#include "piece_factory_base.hpp"
#include "../models/include.hpp"

PieceFactoryBase& PieceFactoryBase::Position(int x, int y) {
    P->position = {static_cast<float>(x), static_cast<float>(y)};
    return *this;
}

PieceFactoryBase& KingPieceFactory::black() {
    P = std::make_shared<King>(GetBlackKingPrototype());
    return *this;
}

PieceFactoryBase& KingPieceFactory::white() {
    P = std::make_shared<King>(GetWhiteKingPrototype());
    return *this;
}

King KingPieceFactory::GetWhiteKingPrototype() {
    static King whiteKing(0, 0, "KingWhite", PieceColor::white);
    return whiteKing;
}

King KingPieceFactory::GetBlackKingPrototype() {
    static King blackKing(0, 0, "KingBlack", PieceColor::black);
    return blackKing;
}


PieceFactoryBase& QueenPieceFactory::black() {
    P = std::make_shared<Queen>(GetBlackQueenPrototype());
    return *this;
}

PieceFactoryBase& QueenPieceFactory::white() {
    P = std::make_shared<Queen>(GetWhiteQueenPrototype());
    return *this;
}

Queen QueenPieceFactory::GetWhiteQueenPrototype() {
    static Queen whiteQueen(0, 0, "QueenWhite", PieceColor::white);
    return whiteQueen;
}

Queen QueenPieceFactory::GetBlackQueenPrototype() {
    static Queen blackQueen(0, 0, "QueenBlack", PieceColor::black);
    return blackQueen;
}


PieceFactoryBase& RookPieceFactory::black() {
    P = std::make_shared<Rook>(GetBlackRookPrototype());
    return *this;
}

PieceFactoryBase& RookPieceFactory::white() {
    P = std::make_shared<Rook>(GetWhiteRookPrototype());
    return *this;
}

Rook RookPieceFactory::GetWhiteRookPrototype() {
    static Rook whiteRook(0, 0, "RookWhite", PieceColor::white);
    return whiteRook;
}

Rook RookPieceFactory::GetBlackRookPrototype() {
    static Rook blackRook(0, 0, "RookBlack", PieceColor::black);
    return blackRook;
}


PieceFactoryBase& HorsePieceFactory::black() {
    P = std::make_shared<Horse>(GetBlackHorsePrototype());
    return *this;
}

PieceFactoryBase& HorsePieceFactory::white() {
    P = std::make_shared<Horse>(GetWhiteHorsePrototype());
    return *this;
}

Horse HorsePieceFactory::GetWhiteHorsePrototype() {
    static Horse whiteHorse(0, 0, "HorseWhite", PieceColor::white);
    return whiteHorse;
}

Horse HorsePieceFactory::GetBlackHorsePrototype() {
    static Horse blackHorse(0, 0, "HorseBlack", PieceColor::black);
    return blackHorse;
}


PieceFactoryBase& BishopPieceFactory::black() {
    P = std::make_shared<Bishop>(GetBlackBishopPrototype());
    return *this;
}

PieceFactoryBase& BishopPieceFactory::white() {
    P = std::make_shared<Bishop>(GetWhiteBishopPrototype());
    return *this;
}

Bishop BishopPieceFactory::GetWhiteBishopPrototype() {
    static Bishop whiteBishop(0, 0, "BishopWhite", PieceColor::white);
    return whiteBishop;
}

Bishop BishopPieceFactory::GetBlackBishopPrototype() {
    static Bishop blackBishop(0, 0, "BishopBlack", PieceColor::black);
    return blackBishop;
}


PieceFactoryBase& PawnPieceFactory::black() {
    P = std::make_shared<Pawn>(GetBlackPawnPrototype());
    return *this;
}

PieceFactoryBase& PawnPieceFactory::white() {
    P = std::make_shared<Pawn>(GetWhitePawnPrototype());
    return *this;
}

Pawn PawnPieceFactory::GetWhitePawnPrototype() {
    static Pawn whitePawn(0, 0, "PawnWhite", PieceColor::white);
    return whitePawn;
}

Pawn PawnPieceFactory::GetBlackPawnPrototype() {
    static Pawn blackPawn(0, 0, "PawnBlack", PieceColor::black);
    return blackPawn;
}