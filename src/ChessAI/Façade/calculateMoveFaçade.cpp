#include "calculateMoveFaçade.hpp"

#include <raymath.h>

#include <unordered_map>

#include "../../chessboard/chessboard.hpp"
#include "../../move/move.hpp"
#include "../../pieces/bases/piece.hpp"
#include "../../pieces/models/king/king.hpp"

calculateMoveFaçade& calculateMoveFaçade::get() {
    static calculateMoveFaçade instance;
    return instance;
}