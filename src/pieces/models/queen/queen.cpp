#include "queen.hpp"
#include "../../factory/piece_factory.hpp"

std::shared_ptr<Piece> Queen::clone() {
    std::shared_ptr<Piece> piece = color == PieceColor::black ? Piece::Create().Queen.black().Position(position.x, position.y) : Piece::Create().Queen.white().Position(position.x, position.y);
    piece->legalMoves = legalMoves;
    return piece;
}