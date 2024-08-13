#pragma once
#include <raylib.h>
#include <memory>

class Piece;
class Chessboard;
class MomentoMove;
enum class PieceColor;

class Move {
   public:
    Move(Vector2 from, Vector2 to, Chessboard& chessboard);
    void init(Vector2 from, Vector2 to, Chessboard& chessboard);
    void MoveAnimation() const;
    void PromoteAnimation() const;
    void Update();
    void ExecuteMove();
    static Move* GetUndoMove(Chessboard &chessboard);
    static void SetMoves(const std::array<std::shared_ptr<Piece>,64> &grid, PieceColor color);

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
    static std::vector<MomentoMove> moveTokens;

   private:
    explicit Move(Chessboard& chessboard);//undo move
    Vector2 from;
    Vector2 to;
    Vector2 AnimationPosition;
    Chessboard& chessboard;
    std::shared_ptr<Piece> piece;
    std::shared_ptr<Piece> rebornPiece = nullptr;
    bool UndoMove = false;


   private:
    void CalculateLegalMoves();
    bool isKingChecked();
    void enPassantCalculation();
    bool isEnemyPawnOn(int x, int y) const;
    void castling() const;
    void promote();
    void CapturePiece(std::shared_ptr<Piece>& p);
};
