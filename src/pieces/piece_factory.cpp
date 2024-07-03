#include "piece_factory.hpp"

std::unordered_map<std::string, std::unique_ptr<Piece>> PieceFactory::prototypes;
void PieceFactory::InitPrototype() {
    prototypes = {
        {"PawnWhite", std::make_unique<Pawn>(0, 0, "PawnWhite", PieceColor::white)},
        {"PawnBlack", std::make_unique<Pawn>(0, 0, "PawnBlack", PieceColor::black)},
        {"KingBlack", std::make_unique<King>(0, 0, "KingBlack", PieceColor::black)},
        {"KingWhite", std::make_unique<King>(0, 0, "KingWhite", PieceColor::white)},
        {"QueenBlack", std::make_unique<Queen>(0, 0, "QueenBlack", PieceColor::black)},
        {"QueenWhite", std::make_unique<Queen>(0, 0, "QueenWhite", PieceColor::white)},
        {"RookBlack", std::make_unique<Rook>(0, 0, "RookBlack", PieceColor::black)},
        {"RookWhite", std::make_unique<Rook>(0, 0, "RookWhite", PieceColor::white)},
        {"HorseBlack", std::make_unique<Horse>(0, 0, "HorseBlack", PieceColor::black)},
        {"HorseWhite", std::make_unique<Horse>(0, 0, "HorseWhite", PieceColor::white)},
        {"BishopBlack", std::make_unique<Bishop>(0, 0, "BishopBlack", PieceColor::black)},
        {"BishopWhite", std::make_unique<Bishop>(0, 0, "BishopWhite", PieceColor::white)}
};
}
