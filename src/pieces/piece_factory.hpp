#pragma once
#include "pieces.hpp"
#include <unordered_map>
#include <raylib.h>
#include <memory>

class PieceFactory {
    PieceFactory() = delete;
    static std::unordered_map<std::string, std::unique_ptr<Piece>> prototypes;
    public:
    static void InitPrototype();

    static std::shared_ptr<Piece> CreatePiece(const std::string& type, float column, float row) {
        auto it = prototypes.find(type);
        if (it != prototypes.end()) {
            std::shared_ptr<Piece> piece = std::make_shared<Piece>(*it->second);
            piece->position = {column, row};
            return piece;
        }
        return nullptr;
    }
};