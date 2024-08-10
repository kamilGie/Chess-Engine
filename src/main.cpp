#include "Menu/Menu.hpp"
#include "stateMachine/stateMahcine.hpp"

int main() {
    InitWindow(800, 800, "chess");
    // for loop to delete Menu object after it's scope

    StateMachine GameStateMachine;
    GameStateMachine.SetState(std::make_unique<Menu>(GameStateMachine));
    while(!WindowShouldClose()){
        GameStateMachine.HandleInput();
        GameStateMachine.Update();
        GameStateMachine.Draw();
    }
    CloseWindow();
}