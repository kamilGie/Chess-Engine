#pragma once
#include <raylib.h>

#include <memory>

class Piece;
class Chessboard;
enum class PieceColor;

class Move {
   public:
    Move(Vector2 from, Vector2 to, Chessboard& chessboard);
    void MoveAnimation();
    void PromoteAnimation();
    void Update();
    void ExecuteMove();
    static void SetMoves(std::array<std::shared_ptr<Piece>,64> grid, PieceColor color);

    bool winningMove = false;
    bool stalematingMove = false;
    bool animationEnd = false;
    bool promotion = false;
    bool AI_promotion = false;

    static Sound moveSound;
    static Sound captureSound;
    static Sound checkSound;
    static Texture2D whitePromotionTexture;
    static Texture2D blackPromotionTexture;

   private:
    Vector2 from;
    Vector2 to;
    Vector2 AnimationPosition;
    Chessboard& chessboard;
    std::shared_ptr<Piece> piece;

   private:
    void CalculateLegalMoves();
    bool isKingChecked();
    void enPassantCalculation();
    bool isEnemyPawnOn(int x, int y);
    void castling();
    void promote();
    void CapturePiece(std::shared_ptr<Piece>& p);
};
