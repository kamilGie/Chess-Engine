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

    SetTargetFPS(60);
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

    DrawRectangleRounded(startButton, 0.2, 0, Color{108, 152, 63, 255});
    DrawText(startButton.text.c_str(), GetScreenWidth() / 2 - MeasureText(startButton.text.c_str(), 30) / 2, GetScreenHeight() - 90, 30, Color{233, 235, 210, 255});
    if (startButton.hover) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawRectangleRoundedLines(startButton, 0.3, 0, 3, Color{233, 235, 210, 255});
    }

    DrawRectangleRounded(PvP, 0.2, 0, Color{233, 235, 210, 255});
    DrawText(PvP.text.c_str(), GetScreenWidth() / 4 - MeasureText(PvP.text.c_str(), 30) / 2 - 50, 210, 30, Color{108, 152, 63, 255});
    if (!PvP.isActive) DrawRectangleRounded(PvP, 0.2, 0, Fade(BLACK, 0.7f));
    if (PvP.hover) { 
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawRectangleRoundedLines(PvP, 0.3, 0, 3, Color{233, 235, 210, 255});
    }

    DrawRectangleRounded(PvAI, 0.2, 0, Color{233, 235, 210, 255});
    DrawText(PvAI.text.c_str(), GetScreenWidth() / 2 - MeasureText(PvAI.text.c_str(), 30) / 2, 210, 30, Color{108, 152, 63, 255});
    if (!PvAI.isActive) DrawRectangleRounded(PvAI, 0.2, 0, Fade(BLACK, 0.7f));
    if (PvAI.hover) {
        DrawRectangleRounded(AiColor, 0.2, 0, AiColor.isActive ? BLACK : WHITE);
        DrawText(AiColor.text.c_str(), GetScreenWidth() / 2 - MeasureText(AiColor.text.c_str(), 30) / 2, 150, 30, Color{108, 152, 63, 255});
        if (!PvAI.isActive) DrawRectangleRounded(AiColor, 0.2, 0, Fade(BLACK, 0.7f));
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if(!AiColor.hover) DrawRectangleRoundedLines(PvAI, 0.3, 0, 3, Color{233, 235, 210, 255});
        else DrawRectangleRoundedLines(AiColor, 0.3, 0, 3, Color{233, 235, 210, 255});
    }

    DrawRectangleRounded(AIvAI, 0.2, 0, Color{233, 235, 210, 255});
    DrawText(AIvAI.text.c_str(), GetScreenWidth() / 4 * 3 - MeasureText(AIvAI.text.c_str(), 30) / 2 + 50, 210, 30, Color{108, 152, 63, 255});
    if (!AIvAI.isActive) DrawRectangleRounded(AIvAI, 0.2, 0, Fade(BLACK, 0.7f));
    if (AIvAI.hover ) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawRectangleRoundedLines(AIvAI, 0.3, 0, 3, Color{233, 235, 210, 255});
    }

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
    }
}
