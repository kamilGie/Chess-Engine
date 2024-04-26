#include "chessboard.hpp"
#include <raylib.h>

Chessboard::Chessboard(){
    cellSize=100;
    cellCount=8;
}

void Chessboard::Draw(){
    bool flag=true;
    for (int row = 0; row < cellCount; row++) {
        for (int column = 0; column < cellCount; column++) {
            if(flag){
            DrawRectangle(row*cellSize,column*cellSize,cellSize,cellSize,BEIGE);
            flag=false;
            }else{
            DrawRectangle(row*cellSize,column*cellSize,cellSize,cellSize,DARKBROWN);
            flag=true;
            }
        }
        flag = !flag;;
    }

}
