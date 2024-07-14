#include "rook.hpp"
#include "../../factory/piece_factory.hpp"

std::shared_ptr<Piece> Rook::clone() {
    std::shared_ptr<Piece> piece = color == PieceColor::black ? Piece::Create().Rook.black().Position(position.x, position.y) : Piece::Create().Rook.white().Position(position.x, position.y);
    piece->legalMoves = legalMoves;
    return piece;
}