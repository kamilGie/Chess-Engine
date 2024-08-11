#pragma once
class StateMachine;

struct State {
    virtual ~State() = default;
    StateMachine& sm;
    explicit State(StateMachine& sm) : sm(sm) {};
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
    void HandleInput() const{
        state->HandleInput();
    };
    void Update() const{
        state->Update();
    };
    void Draw() const{
        state->Draw();
    };
};