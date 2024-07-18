#pragma once
#include <raylib.h>
#include <string>
#include <vector>

class Drawable {
    public:
    ~Drawable() = default;
    virtual void Draw() = 0;
};

class MenuButton : public Drawable {
    public:
    MenuButton(Rectangle button, const std::string& text, Color BackgroundColor= Color{233, 235, 210, 255}, Color TextColor= Color{108, 152, 63, 255});
    Rectangle button;
    bool hover = false;
    bool isActive = false;
    Color BackgroundColor;
    Color TextColor;
    std::string text;


    void Draw() override;

    operator Rectangle() const { return button; }

};

class MenuButtonsGroup : public Drawable{
    public:
    MenuButtonsGroup()=default;
    std::vector<Drawable*> MainButtons;
    std::vector<Drawable*> ButtonsAfterHover;
    void Draw() override;
    bool hover = false;
};