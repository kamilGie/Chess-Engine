#include "Menu.hpp"

#include <raylib.h>

#include <fstream>

Menu::Menu() {
    std::ifstream file("../src/GameSettings.txt");
    std::string text;
    while (file >> text) {
        if (text == "PvAI") {
            file >> text;
            isPvAI = (text == "true") ? true : false;
        } else if (text == "ChessAIColor") {
            file >> text;
            isAIBlack = (text == "black") ? true : false;
        } else if (text == "TargetFPS") {
            file >> fps;
        } else if (text == "PvP") {
            file >> text;
            isPVP = (text == "true") ? true : false;
        } else if (text == "AIvAI") {
            file >> text;
            isAIvsAI = (text == "true") ? true : false;
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
    if (!hasSettingsChanged) return;

    std::ofstream file("../src/GameSettings.txt");
    if (file.is_open()) {
        file << "PvP " << (isPVP ? "true\n" : "false\n");
        file << "PvAI " << (isPvAI ? "true\n" : "false\n");
        file << "AIvAI " << (isAIvsAI ? "true\n" : "false\n");
        file << "ChessAIColor " << (isAIBlack ? "black\n" : "white\n");
        file << "TargetFPS " << fps;
        file.close();
    }
}

void Menu::Draw() {
    BeginDrawing();
    DrawTexture(MenuBackground, 0, 0, WHITE);

    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    DrawRectangleRounded(startButton, 0.2, 0, Color{108, 152, 63, 255});
    DrawText("Start Game", GetScreenWidth() / 2 - MeasureText("Start Game", 30) / 2, GetScreenHeight() - 90, 30, Color{233, 235, 210, 255});
    if (startButtonHover) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawRectangleRoundedLines(startButton, 0.3, 0, 3, Color{233, 235, 210, 255});
    }

    DrawRectangleRounded(PvP, 0.2, 0, Color{233, 235, 210, 255});
    DrawText("PvP", GetScreenWidth() / 4 - MeasureText("PvP", 30) / 2 - 50, 210, 30, Color{108, 152, 63, 255});
    if (!isPVP) DrawRectangleRounded(PvP, 0.2, 0, Fade(BLACK, 0.7f));
    if (PvPHover) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawRectangleRoundedLines(PvP, 0.3, 0, 3, Color{233, 235, 210, 255});
    }

    DrawRectangleRounded(PvAI, 0.2, 0, Color{233, 235, 210, 255});
    DrawText("PvAI", GetScreenWidth() / 2 - MeasureText("PvAI", 30) / 2, 210, 30, Color{108, 152, 63, 255});
    if (!isPvAI) DrawRectangleRounded(PvAI, 0.2, 0, Fade(BLACK, 0.7f));
    if (PvAIHover) {
        DrawRectangleRounded(AIColor, 0.2, 0, isAIBlack ? BLACK : WHITE);
        DrawText("AI Color", GetScreenWidth() / 2 - MeasureText("AI Color", 30) / 2, 150, 30, Color{108, 152, 63, 255});
        if (!isPvAI) DrawRectangleRounded(AIColor, 0.2, 0, Fade(BLACK, 0.7f));
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if(!AIColorHover) DrawRectangleRoundedLines(PvAI, 0.3, 0, 3, Color{233, 235, 210, 255});
        else DrawRectangleRoundedLines(AIColor, 0.3, 0, 3, Color{233, 235, 210, 255});
    }

    DrawRectangleRounded(AIvsAI, 0.2, 0, Color{233, 235, 210, 255});
    DrawText("AIvsAI", GetScreenWidth() / 4 * 3 - MeasureText("AIvsAI", 30) / 2 + 50, 210, 30, Color{108, 152, 63, 255});
    if (!isAIvsAI) DrawRectangleRounded(AIvsAI, 0.2, 0, Fade(BLACK, 0.7f));
    if (AIvsAIHover) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawRectangleRoundedLines(AIvsAI, 0.3, 0, 3, Color{233, 235, 210, 255});
    }

    EndDrawing();
}

void Menu::Update() {
}

void Menu::HandleInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), startButton)) running = false;
        if (CheckCollisionPointRec(GetMousePosition(), PvP)) {
            isPVP = true;
            isPvAI = false;
            isAIvsAI = false;
            hasSettingsChanged = true;
        }

        if (CheckCollisionPointRec(GetMousePosition(), PvAI)) {
            isPvAI = true;
            isPVP = false;
            isAIvsAI = false;
            hasSettingsChanged = true;
        }

        if (CheckCollisionPointRec(GetMousePosition(), AIvsAI)) {
            isAIvsAI = true;
            isPvAI = false;
            isPVP = false;
            hasSettingsChanged = true;
        }

        if (PvAIHover && CheckCollisionPointRec(GetMousePosition(), AiColorMargin)) {
            isAIBlack = !isAIBlack;
            hasSettingsChanged = true;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), startButton)) {
        startButtonHover = true;
    } else if (CheckCollisionPointRec(GetMousePosition(), PvP)) {
        PvPHover = true;
    } else if (CheckCollisionPointRec(GetMousePosition(), PvAI)) {
        PvAIHover = true;
        AIColorHover = false;
    } else if (CheckCollisionPointRec(GetMousePosition(), AIvsAI)) {
        AIvsAIHover = true;
    } else if(PvAIHover && isPvAI &&   CheckCollisionPointRec(GetMousePosition(), AiColorMargin)) {
        AIColorHover = true;
    } else {
        startButtonHover = false;
        PvPHover = false;
        PvAIHover = false;
        AIvsAIHover = false;
        AIColorHover = false;
    }
}
