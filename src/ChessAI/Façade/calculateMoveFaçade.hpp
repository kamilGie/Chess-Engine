#pragma once
#include <raylib.h>
#include <memory>
#include <array>

class Piece;
enum class PieceColor;

class calculateMoveFaçade {
    public:
        static calculateMoveFaçade& get();

        float CalculateMove(Vector2 from , Vector2 to, std::array<std::shared_ptr<Piece>,64> grid,PieceColor,int depth=0);
    private:
        calculateMoveFaçade() = default;
        ~calculateMoveFaçade() = default;
        calculateMoveFaçade(const calculateMoveFaçade&) = delete;
        calculateMoveFaçade& operator=(const calculateMoveFaçade&) = delete;
};