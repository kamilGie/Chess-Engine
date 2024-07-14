#include "bishop.hpp"
#include "../../factory/piece_factory.hpp"

std::shared_ptr<Piece> Bishop::clone() {
    std::shared_ptr<Piece> piece = color == PieceColor::black ? Piece::Create().Bishop.black().Position(position.x, position.y) : Piece::Create().Bishop.white().Position(position.x, position.y);
    piece->legalMoves = legalMoves;
    return piece;
}