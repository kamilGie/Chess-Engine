#include <iostream>
#include <raylib.h>
#include "chessboard.hpp"

using namespace std;

int main () {

    Chessboard chessboard = Chessboard();

    InitWindow(chessboard.cellSize*chessboard.cellCount, chessboard.cellSize*chessboard.cellCount, "chess");
    SetTargetFPS(120);


    while (!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(BLACK);
        chessboard.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}