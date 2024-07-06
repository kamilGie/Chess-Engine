#include "piece_factory.hpp"

void PieceFactory::UnloadTextures() {
    for (auto texture : Textures) {
        UnloadTexture(*texture);
    }
    Textures.clear();
}

std::vector<Texture2D*> PieceFactory::Textures = {};