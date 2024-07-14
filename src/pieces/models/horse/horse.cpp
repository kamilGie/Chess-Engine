#include "horse.hpp"
#include "../../factory/piece_factory.hpp"

std::shared_ptr<Piece> Horse::clone() {
    std::shared_ptr<Piece> piece = color == PieceColor::black ? Piece::Create().Horse.black().Position(position.x, position.y) : Piece::Create().Horse.white().Position(position.x, position.y);
    piece->legalMoves = legalMoves;
    return piece;
}