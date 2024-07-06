#pragma once
#include <vector>
#include <raylib.h>
#include "piece_factory_base.hpp"

class PieceFactory {
   public:
    KingPieceFactory King;
    QueenPieceFactory Queen;
    RookPieceFactory Rook;
    HorsePieceFactory Horse;
    BishopPieceFactory Bishop;
    PawnPieceFactory Pawn;

    static void UnloadTextures();
    static std::vector<Texture2D*> Textures;
};