#pragma once
#include <raylib.h>
#include <string>

class MenuButton{
    public:
    MenuButton(Rectangle button, const std::string& text);
    Rectangle button;
    bool hover = false;
    bool isActive = false;
    std::string text;

    operator Rectangle() const { return button; }

};