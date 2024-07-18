#include "MenuButton.hpp"

MenuButton::MenuButton(Rectangle button,const std::string& text,Color BackgroundColor, Color TextColor): button(button),BackgroundColor(BackgroundColor),TextColor(TextColor),text(text) {}

void MenuButton::Draw() {
    DrawRectangleRounded(button, 0.2, 0, BackgroundColor );
    DrawText(text.c_str(), button.x + button.width / 2 - MeasureText(text.c_str(), 30) / 2, button.y + button.height / 2 - 15, 30, TextColor);
    if (!isActive) DrawRectangleRounded(button, 0.2, 0, Fade(BLACK, 0.7f));
    if (hover) { 
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawRectangleRoundedLines(button, 0.4, 0, 3, WHITE );
    }

}

void MenuButtonsGroup::Draw() {
    for (auto&& button : MainButtons) {
        button->Draw();
    }
    if (hover) {
        for (auto&& button : ButtonsAfterHover) {
            button->Draw();
        }
    }

}