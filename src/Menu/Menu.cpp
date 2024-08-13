#include "Menu.hpp"

#include <raylib.h>
#include <fstream>
#include "../game.hpp"

Menu::Menu(StateMachine& sm) :State(sm),fps(60) {
    std::ifstream file("../src/GameSettings.txt");
    std::string text;
    while (file >> text) {
        if (text == "PvAI") {
            file >> text;
            PvAI.isActive = (text == "true");
        } else if (text == "ChessAIColor") {
            file >> text;
            AiColorBlack.isActive = (text == "black");
            AIColorWHite.isActive = (text == "white");
        } else if (text == "TargetFPS") {
            file >> fps;
        } else if (text == "PvP") {
            file >> text;
            PvP.isActive = (text == "true");
        } else if (text == "AIvAI") {
            file >> text;
            AIvAI.isActive = (text == "true");
        }
    }
    file.close();

    const std::string fullPath = "../Graphics/menu.png";
    const Image image = LoadImage(fullPath.c_str());
    MenuBackground = LoadTextureFromImage(image);
    UnloadImage(image);

    InitButtons();
    startButton.isActive = true;
    SetTargetFPS(120);
}

void Menu::InitButtons() {
    PvsAIGroup.AddMainButton(&PvAI);
    PvsAIGroup.AddButtonAfterHover(&AiColorBlack);
    PvsAIGroup.AddButtonAfterHover(&AIColorWHite);

    AllButtons.AddMainButton(&startButton);
    AllButtons.AddMainButton(&PvP);
    AllButtons.AddMainButton(&AIvAI);
    AllButtons.AddMainButton(&PvsAIGroup);
}

Menu::~Menu() {
    UnloadTexture(MenuBackground);
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void Menu::Draw() {
    BeginDrawing();
    DrawTexture(MenuBackground, 0, 0, WHITE);
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    AllButtons.Draw();
    EndDrawing();
}

void Menu::Update() {
}

void Menu::UpdateParams() const {
    if (std::ofstream file("../src/GameSettings.txt"); file.is_open()) {
        file << "PvP " << (PvP.isActive ? "true\n" : "false\n");
        file << "PvAI " << (PvAI.isActive ? "true\n" : "false\n");
        file << "ChessAIColor " << (AiColorBlack.isActive ? "black\n" : "white\n");
        file << "AIvAI " << (AIvAI.isActive ? "true\n" : "false\n");
        file << "TargetFPS " << fps;
        file.close();
    }

}

void Menu::HandleInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), startButton)) {
            if (hasSettingsChanged) UpdateParams();
            sm.SetState(std::make_unique<Game>(sm));
        }
        if (CheckCollisionPointRec(GetMousePosition(), PvP)) {
            PvP.isActive = true;
            PvAI.isActive = false;
            AIvAI.isActive = false;
            hasSettingsChanged = true;
        }

        if (CheckCollisionPointRec(GetMousePosition(), PvAI)) {
            PvAI.isActive = true;
            PvP.isActive = false;
            AIvAI.isActive = false;
            hasSettingsChanged = true;
        }

        if (CheckCollisionPointRec(GetMousePosition(), AIvAI)) {
            AIvAI.isActive = true;
            PvP.isActive = false;
            PvAI.isActive = false;
            hasSettingsChanged = true;
        }

        if (PvAI.hover && (CheckCollisionPointRec(GetMousePosition(), AIColorWHite ) || CheckCollisionPointRec(GetMousePosition(), AiColorBlack))) {
            AiColorBlack.isActive = false;
            AIColorWHite.isActive = true;
            hasSettingsChanged = true;
        }

        if (CheckCollisionPointRec(GetMousePosition(), AiColorBlack)) {
            AiColorBlack.isActive = true;
            AIColorWHite.isActive = false;
            hasSettingsChanged = true;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), startButton)) {
        startButton.hover = true;
    } else if (CheckCollisionPointRec(GetMousePosition(), PvP)) {
        PvP.hover = true;
    } else if (CheckCollisionPointRec(GetMousePosition(), PvAI)) {
        PvAI.hover = true;
        AiColorBlack.hover = false;
        AIColorWHite.hover = false;
        PvsAIGroup.hover = true;
    } else if (CheckCollisionPointRec(GetMousePosition(), AIvAI)) {
        AIvAI.hover = true;
    } else if(PvAI.hover && PvAI.isActive &&   CheckCollisionPointRec(GetMousePosition() , PvsAIGroup.area)) {
        if (CheckCollisionPointRec(GetMousePosition(),AiColorBlack)) {
            AiColorBlack.hover = true;
            AIColorWHite.hover = false;
        }else if (CheckCollisionPointRec(GetMousePosition(),AIColorWHite)) {
            AIColorWHite.hover = true;
            AiColorBlack.hover = false;
        }
    }else if (PvAI.hover && PvAI.isActive && CheckCollisionPointRec(GetMousePosition(), AiColorBlack)) {
        AiColorBlack.hover = true;
    } else {
        startButton.hover = false;
        PvP.hover = false;
        PvAI.hover = false;
        AIvAI.hover = false;
        AiColorBlack.hover = false;
        AIColorWHite.hover = false;
        PvsAIGroup.hover = false;
    }
}
