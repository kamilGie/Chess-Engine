#include "Menu/Menu.hpp"
#include "stateMachine/stateMahcine.hpp"
#include <memory>

int main() {
    InitWindow(800, 800, "chess");
    StateMachine GameStateMachine;
    GameStateMachine.SetState(std::make_unique<Menu>(GameStateMachine));
    while(!WindowShouldClose()){
        GameStateMachine.HandleInput();
        GameStateMachine.Update();
        GameStateMachine.Draw();
    }
    CloseWindow();
}