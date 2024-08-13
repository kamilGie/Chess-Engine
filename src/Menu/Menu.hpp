#pragma once
#include <raylib.h>
#include "buttonsDecorators/BD.hpp"
#include "../stateMachine/stateMahcine.hpp"


class Menu : public State{
   public:
    explicit  Menu(StateMachine & sm);
    ~Menu() override;
    void Draw() override;
    void Update() override;

    void UpdateParams() const;

    void HandleInput() override;
    bool running = true;
    bool quit = false;
    private:
    void InitButtons();

    ButtonColorDecorator<MenuButton> startButton{
        Color{108, 152, 63, 255}, Color{233, 235, 210, 255},
        MenuButton{{ static_cast<float>(GetScreenWidth()) / 2 - 140, static_cast<float>(GetScreenHeight()) - 100, 280, 50 }, "Start Game"
    }};
    ButtonStateDecorator<MenuButton> PvP{MenuButton{ { static_cast<float>(GetScreenWidth()) / 4 - 150,  200, 200, 50 }, "PvP"}};
    ButtonStateDecorator<MenuButton> PvAI{MenuButton{ { static_cast<float>(GetScreenWidth()) / 2 - 100,  200, 200, 50 }, "PvAI"}};
    ButtonStateDecorator<MenuButton> AIvAI{MenuButton{ { static_cast<float>(GetScreenWidth()) / 4 * 3 - 50,  200, 200, 50 }, "AIvAI"}};
    ButtonColorDecorator<ButtonStateDecorator<MenuButton>> AiColorBlack{ BLACK, Color{108, 152, 63, 255},  MenuButton{{ static_cast<float>(GetScreenWidth()) / 2 - 100,  140, 90,50 }, "Black"}};
    ButtonColorDecorator<ButtonStateDecorator<MenuButton>> AIColorWHite{ WHITE, Color{108, 152, 63, 255}, MenuButton{{ static_cast<float>(GetScreenWidth()) / 2 + 10,  140, 90,50 }, "White"}};

    MenuButtonsGroup PvsAIGroup;
    MenuButtonsGroup AllButtons;
    

    int fps;
    bool hasSettingsChanged=false;

    Texture2D MenuBackground;
};