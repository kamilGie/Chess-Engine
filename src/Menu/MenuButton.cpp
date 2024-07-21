#include "MenuButton.hpp"

MenuButton::MenuButton(Rectangle area,const std::string& text):text(text) {
    this->area = area;
}

void MenuButton::Draw() {
    DrawRectangleRounded(area, 0.2, 0, BackgroundColor );
    DrawText(text.c_str(), area.x + area.width / 2 - MeasureText(text.c_str(), 30) / 2, area.y + area.height / 2 - 15, 30, TextColor);
    if (hover) { 
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawRectangleRoundedLines(area, 0.4, 0, 3, WHITE );
    }

}

void MenuButtonsGroup::ExpendedArea(Drawable* button) {
    if (MainButtons.empty() && ButtonsAfterHover.empty()) area = button->area;
    else {
        float originalX = area.x;
        float originalY = area.y;
        area.width  = std::max(originalX + area.width, button->area.x + button->area.width) - std::min(originalX, button->area.x);
        area.height = std::max(originalY + area.height, button->area.y + button->area.height) - std::min(originalY, button->area.y);
        area.x = std::min(originalX, button->area.x);
        area.y = std::min(originalY, button->area.y);
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

void MenuButtonsGroup::AddMainButton(Drawable* button) {
    ExpendedArea(button);
    MainButtons.push_back(button);
}

void MenuButtonsGroup::AddButtonAfterHover(Drawable* button) {
    ExpendedArea(button);
    ButtonsAfterHover.push_back(button);
}
