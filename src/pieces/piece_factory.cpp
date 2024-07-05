#include "piece_factory.hpp"
#include "pieces.hpp"

std::shared_ptr<Pawn> PieceFactory::BlackPawn(int x, int y) {
    auto newPiece = std::make_shared<Pawn>(GetBlackPawnPrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
}

std::shared_ptr<Pawn> PieceFactory::WhitePawn(int x, int y) {
    auto newPiece = std::make_shared<Pawn>(GetWhitePawnPrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
}

std::shared_ptr<Rook> PieceFactory::BlackRook(int x, int y) {
    auto newPiece = std::make_shared<Rook>(GetBlackRookPrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
}

std::shared_ptr<Rook> PieceFactory::WhiteRook(int x, int y) {
    auto newPiece = std::make_shared<Rook>(GetWhiteRookPrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
}

std::shared_ptr<Horse> PieceFactory::BlackHorse(int x, int y) {
    auto newPiece = std::make_shared<Horse>(GetBlackHorsePrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
}

std::shared_ptr<Horse> PieceFactory::WhiteHorse(int x, int y) {
    auto newPiece = std::make_shared<Horse>(GetWhiteHorsePrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
}

std::shared_ptr<Bishop> PieceFactory::BlackBishop(int x, int y) {
    auto newPiece = std::make_shared<Bishop>(GetBlackBishopPrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
}

std::shared_ptr<Bishop> PieceFactory::WhiteBishop(int x, int y) {
    auto newPiece = std::make_shared<Bishop>(GetWhiteBishopPrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
}

std::shared_ptr<Queen> PieceFactory::BlackQueen(int x, int y) {
    auto newPiece = std::make_shared<Queen>(GetBlackQueenPrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
}

std::shared_ptr<Queen> PieceFactory::WhiteQueen(int x, int y) {
    auto newPiece = std::make_shared<Queen>(GetWhiteQueenPrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
}

std::shared_ptr<King> PieceFactory::BlackKing(int x, int y) {
    auto newPiece = std::make_shared<King>(GetBlackKingPrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
}

std::shared_ptr<King> PieceFactory::WhiteKing(int x, int y) {
    auto newPiece = std::make_shared<King>(GetWhiteKingPrototype());
    newPiece->position = {static_cast<float>(x), static_cast<float>(y)};
    return newPiece;
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
