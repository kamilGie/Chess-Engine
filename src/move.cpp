#include "move.hpp"

void Move::MoveAnimation() {
    DrawTexture(piece->texture, from.x , from.y, WHITE);
}

bool Move::MoveCalculation() {
        if (Vector2Distance(from, to) > 0.1f) {
            from = Vector2Lerp(from, to, 0.2f);
            return false;
        } else {
            return true;
        }
}
