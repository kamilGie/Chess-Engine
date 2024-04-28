#include "game.hpp"

#include <iostream>
#include <algorithm>
#include <raymath.h>


int cellSize = 100;

Game::Game() {
    blackPieces.push_back(new KingBlack(0, 3));
    blackPieces.push_back(new QueenBlack(0, 4));
    blackPieces.push_back(new RookBlack(0, 0));
    blackPieces.push_back(new RookBlack(0, 7));
    blackPieces.push_back(new HorseBlack(0, 1));
    blackPieces.push_back(new HorseBlack(0, 6));
    blackPieces.push_back(new BishopBlack(0, 2));
    blackPieces.push_back(new BishopBlack(0, 5));

    whitePieces.push_back(new KingWhite(7, 3));
    whitePieces.push_back(new QueenWhite(7, 4));
    whitePieces.push_back(new RookWhite(7, 0));
    whitePieces.push_back(new RookWhite(7, 7));
    whitePieces.push_back(new HorseWhite(7, 1));
    whitePieces.push_back(new HorseWhite(7, 6));
    whitePieces.push_back(new BishopWhite(7, 2));
    whitePieces.push_back(new BishopWhite(7, 5));

    for (int i = 0; i < 8; ++i) {
        blackPieces.push_back(new PawnBlack(1, i));
        whitePieces.push_back(new PawnWhite(6, i));
    }
}

Game::~Game() {
    for (auto piece : blackPieces) {
        delete piece;
    }

    for (auto piece : whitePieces) {
        delete piece;
    }
}

void Game::Move() {

    if(clickedPiece!=nullptr){
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            clickedPiece->position.x=GetMouseX()/cellSize;
            clickedPiece->position.y=GetMouseY()/cellSize;
            clickedPiece=nullptr;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        int x = GetMouseX()/cellSize;
        int y = GetMouseY()/cellSize;
        for (auto piece : whitePieces) {
            if(Vector2Equals(piece->position,{(float)x,(float)y})){
                clickedPiece=piece;
            }
         }
    }

}


void Game::Draw() {
    chessboard.Draw();

    Move();


    for (auto blackP : blackPieces) {
        blackP->Draw();
    }

    for (auto whiteP : whitePieces) {
        whiteP->Draw();
    }
}
