#include <iostream>
#include <raylib.h>

using namespace std;

int main () {

    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "program");
    SetTargetFPS(120);

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}