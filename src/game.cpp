#include "game.hpp"

void Game::Draw(){
    chessboard.Draw();
    horse.Draw();
    horse.Move();
}
