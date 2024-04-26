#include "game.hpp"

void Game::Draw(){
    chessboard.Draw();

    horseBlackB.Draw();
    horseBlackG.Draw();
    horseWhiteB.Draw();
    horseWhiteG.Draw();

    rookBlackA.Draw();
    rookBlackH.Draw();
    rookWhiteA.Draw();
    rookWhiteH.Draw();

    bishopBlackC.Draw();
    bishopBlackF.Draw();
    bishopWhiteC.Draw();
    bishopWhiteF.Draw();

    queenBlack.Draw();
    queenWhite.Draw();

    kingBlack.Draw();
    kingWhite.Draw();

    PawnBlackA.Draw();
    PawnBlackB.Draw();
    PawnBlackC.Draw();
    PawnBlackD.Draw();
    PawnBlackE.Draw();
    PawnBlackF.Draw();
    PawnBlackG.Draw();
    PawnBlackH.Draw();

    PawnWhiteA.Draw();
    PawnWhiteB.Draw();
    PawnWhiteC.Draw();
    PawnWhiteD.Draw();
    PawnWhiteE.Draw();
    PawnWhiteF.Draw();
    PawnWhiteG.Draw();
    PawnWhiteH.Draw();

}
