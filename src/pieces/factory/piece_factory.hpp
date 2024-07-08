#pragma once
#include <raylib.h>

#include <vector>

#include "piece_factory_base.hpp"

// signelton class
class PieceFactory {
   public:
    KingPieceFactory King;
    QueenPieceFactory Queen;
    RookPieceFactory Rook;
    HorsePieceFactory Horse;
    BishopPieceFactory Bishop;
    PawnPieceFactory Pawn;

    static PieceFactory& Get() {
        static PieceFactory instance;
        return instance;
    }

    void UnloadTextures();
    void addTexture(Texture2D* texture);

   private:
    std::vector<Texture2D*> textures={};

    PieceFactory()=default;
    PieceFactory(const PieceFactory&) = delete;
    PieceFactory& operator=(const PieceFactory&) = delete;
};