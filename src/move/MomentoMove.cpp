#include "MomentoMove.hpp"    
#include "../pieces/bases/piece.hpp"
MomentoMove::MomentoMove(Vector2 from, Vector2 to, std::shared_ptr<Piece> capturedPiece): from(from), to(to), capturedPiece(capturedPiece){}
