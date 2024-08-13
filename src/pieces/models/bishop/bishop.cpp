#include "bishop.hpp"
#include "../../factory/piece_factory.hpp"

std::shared_ptr<Piece> Bishop::clone() {
    std::shared_ptr<Piece> piece = color == PieceColor::black ? Piece::Create().Bishop.black().Position(static_cast<int>(position.x), static_cast<int>(position.y)) : Piece::Create().Bishop.white().Position(static_cast<int>(position.x), static_cast<int>(position.y));
    piece->legalMoves = legalMoves;
    return piece;
}