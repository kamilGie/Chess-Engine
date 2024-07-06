#include "piece_factory.hpp"
#include "pieces.hpp"

PieceFactory& PieceFactory::PawnWhite() {
    P = std::make_shared<Pawn>(GetWhitePawnPrototype());
    return *this;
}

PieceFactory& PieceFactory::PawnBlack() {
    P = std::make_shared<Pawn>(GetBlackPawnPrototype());
    return *this;
}

PieceFactory& PieceFactory::RookWhite() {
    P = std::make_shared<Rook>(GetWhiteRookPrototype());
    return *this;
}

PieceFactory& PieceFactory::RookBlack() {
    P = std::make_shared<Rook>(GetBlackRookPrototype());
    return *this;
}

PieceFactory& PieceFactory::HorseWhite() {
    P = std::make_shared<Horse>(GetWhiteHorsePrototype());
    return *this;
}

PieceFactory& PieceFactory::HorseBlack() {
    P = std::make_shared<Horse>(GetBlackHorsePrototype());
    return *this;
}

PieceFactory& PieceFactory::BishopWhite() {
    P = std::make_shared<Bishop>(GetWhiteBishopPrototype());
    return *this;
}

PieceFactory& PieceFactory::BishopBlack() {
    P = std::make_shared<Bishop>(GetBlackBishopPrototype());
    return *this;
}

PieceFactory& PieceFactory::QueenWhite() {
    P = std::make_shared<Queen>(GetWhiteQueenPrototype());
    return *this;
}

PieceFactory& PieceFactory::QueenBlack() {
    P = std::make_shared<Queen>(GetBlackQueenPrototype());
    return *this;
}

PieceFactory& PieceFactory::KingWhite() {
    P = std::make_shared<King>(GetWhiteKingPrototype());
    return *this;
}

PieceFactory& PieceFactory::KingBlack() {
    P = std::make_shared<King>(GetBlackKingPrototype());
    return *this;
}

PieceFactory& PieceFactory::Position(int x, int y) {
    P->position = {static_cast<float>(x), static_cast<float>(y)};
    return *this;
}

void PieceFactory::UnloadTextures() {
    UnloadTexture(GetWhitePawnPrototype().texture);
    UnloadTexture(GetBlackPawnPrototype().texture);
    UnloadTexture(GetWhiteRookPrototype().texture);
    UnloadTexture(GetBlackRookPrototype().texture);
    UnloadTexture(GetWhiteHorsePrototype().texture);
    UnloadTexture(GetBlackHorsePrototype().texture);
    UnloadTexture(GetWhiteBishopPrototype().texture);
    UnloadTexture(GetBlackBishopPrototype().texture);
    UnloadTexture(GetWhiteQueenPrototype().texture);
    UnloadTexture(GetBlackQueenPrototype().texture);
    UnloadTexture(GetWhiteKingPrototype().texture);
    UnloadTexture(GetBlackKingPrototype().texture);
}

Pawn PieceFactory::GetBlackPawnPrototype() {
    static Pawn blackPawn(0, 0, "PawnBlack", PieceColor::black);
    return blackPawn;
}

Pawn PieceFactory::GetWhitePawnPrototype() {
    static Pawn whitePawn(0, 0, "PawnWhite", PieceColor::white);
    return whitePawn;
}

Rook PieceFactory::GetWhiteRookPrototype() {
    static Rook whiteRook(0, 0, "RookWhite", PieceColor::white);
    return whiteRook;
}

Rook PieceFactory::GetBlackRookPrototype() {
    static Rook blackRook(0, 0, "RookBlack", PieceColor::black);
    return blackRook;
}

Horse PieceFactory::GetWhiteHorsePrototype() {
    static Horse whiteHorse(0, 0, "HorseWhite", PieceColor::white);
    return whiteHorse;
}

Horse PieceFactory::GetBlackHorsePrototype() {
    static Horse blackHorse(0, 0, "HorseBlack", PieceColor::black);
    return blackHorse;
}

Bishop PieceFactory::GetWhiteBishopPrototype() {
    static Bishop whiteBishop(0, 0, "BishopWhite", PieceColor::white);
    return whiteBishop;
}

Bishop PieceFactory::GetBlackBishopPrototype() {
    static Bishop blackBishop(0, 0, "BishopBlack", PieceColor::black);
    return blackBishop;
}

Queen PieceFactory::GetWhiteQueenPrototype() {
    static Queen whiteQueen(0, 0, "QueenWhite", PieceColor::white);
    return whiteQueen;
}

Queen PieceFactory::GetBlackQueenPrototype() {
    static Queen blackQueen(0, 0, "QueenBlack", PieceColor::black);
    return blackQueen;
}

King PieceFactory::GetWhiteKingPrototype() {
    static King whiteKing(0, 0, "KingWhite", PieceColor::white);
    return whiteKing;
}

King PieceFactory::GetBlackKingPrototype() {
    static King blackKing(0, 0, "KingBlack", PieceColor::black);
    return blackKing;
}
