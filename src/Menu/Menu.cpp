#include "Menu.hpp"

#include <raylib.h>

#include <fstream>

Menu::Menu() {
    std::ifstream file("../src/GameSettings.txt");
    std::string text;
    while (file >> text) {
        if (text == "PvAI") {
            file >> text;
            PvAI.isActive = (text == "true") ? true : false;
        } else if (text == "ChessAIColor") {
            file >> text;
            AiColor.isActive = (text == "black") ? true : false;
        } else if (text == "TargetFPS") {
            file >> fps;
        } else if (text == "PvP") {
            file >> text;
            PvP.isActive = (text == "true") ? true : false;
        } else if (text == "AIvAI") {
            file >> text;
            AIvAI.isActive = (text == "true") ? true : false;
        }
    }
    file.close();

    std::string fullPath = "../Graphics/menu.png";
    Image image = LoadImage(fullPath.c_str());
    MenuBackground = LoadTextureFromImage(image);
    UnloadImage(image);

    InitButtons();
    startButton.isActive = true;
    SetTargetFPS(60);
}

void Menu::InitButtons() {
    PvsAIGroup.MainButtons.push_back(&PvAI);
    PvsAIGroup.ButtonsAfterHover.push_back(&AiColor);

    AllButtons.MainButtons.push_back(&PvP);
    AllButtons.MainButtons.push_back(&AIvAI);
    AllButtons.MainButtons.push_back(&PvsAIGroup);
    AllButtons.MainButtons.push_back(&startButton);
}

Menu::~Menu() {
    UnloadTexture(MenuBackground);
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    if (!hasSettingsChanged) return;

    std::ofstream file("../src/GameSettings.txt");
    if (file.is_open()) {
        file << "PvP " << (PvP.isActive ? "true\n" : "false\n");
        file << "PvAI " << (PvAI.isActive ? "true\n" : "false\n");
        file << "ChessAIColor " << (AiColor.isActive ? "black\n" : "white\n");
        file << "AIvAI " << (AIvAI.isActive ? "true\n" : "false\n");
        file << "TargetFPS " << fps;
        file.close();
    }
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

void Menu::HandleInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), startButton)) running = false;
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

        if (PvAI.hover && CheckCollisionPointRec(GetMousePosition(), AiColorMargin)) {
            AiColor.isActive = !AiColor.isActive;
            hasSettingsChanged = true;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), startButton)) {
        startButton.hover = true;
    } else if (CheckCollisionPointRec(GetMousePosition(), PvP)) {
        PvP.hover = true;
    } else if (CheckCollisionPointRec(GetMousePosition(), PvAI)) {
        PvAI.hover = true;
        AiColor.hover = false;
        PvsAIGroup.hover = true;
    } else if (CheckCollisionPointRec(GetMousePosition(), AIvAI)) {
        AIvAI.hover = true;
    } else if(PvAI.hover && PvAI.isActive &&   CheckCollisionPointRec(GetMousePosition(), AiColorMargin)) {
        AiColor.hover = true;
    } else {
        startButton.hover = false;
        PvP.hover = false;
        PvAI.hover = false;
        AIvAI.hover = false;
        AiColor.hover = false;
        PvsAIGroup.hover = false;
    }
}