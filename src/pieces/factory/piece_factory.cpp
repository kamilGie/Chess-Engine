#include "piece_factory.hpp"

void PieceFactory::UnloadTextures() {
    for (auto texture : textures) {
        UnloadTexture(*texture);
    }
    textures.clear();
}

void PieceFactory::addTexture(Texture2D* texture) {
    textures.push_back(texture);
}
