#pragma once
#include <memory>
class StateMachine;

struct State {
    virtual ~State() = default;
    StateMachine& sm;
    State(StateMachine& sm) : sm(sm) {};
    virtual void HandleInput() {};
    virtual void Update() {};
    virtual void Draw() {};
};

class StateMachine {
    std::unique_ptr<State> state;

   public:
   void SetState(std::unique_ptr<State> state){
    this->state = std::move(state);
   }
    void HandleInput() {
        state->HandleInput();
    };
    void Update() {
        state->Update();
    };
    void Draw() {
        state->Draw();
    };
};