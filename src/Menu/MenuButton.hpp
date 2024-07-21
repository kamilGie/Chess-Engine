#pragma once
#include <raylib.h>

#include <string>
#include <vector>

class Drawable {
   public:
    ~Drawable() = default;
    Rectangle area;
    virtual void Draw() = 0;
};

class MenuButton : public Drawable {
   public:
    MenuButton(Rectangle area, const std::string& text, Color BackgroundColor = Color{233, 235, 210, 255}, Color TextColor = Color{108, 152, 63, 255});
    bool hover = false;
    bool isActive = false;
    Color BackgroundColor;
    Color TextColor;
    std::string text;

    void Draw() override;

    operator Rectangle() const { return area; }
};


class MenuButtonsGroup : public Drawable {
   public:
    void Draw() override;
    void AddMainButton(Drawable* button);
    void AddButtonAfterHover(Drawable* button);
    bool hover = false;

   private:
    void ExpendedArea(Drawable* button);
    std::vector<Drawable*> MainButtons;
    std::vector<Drawable*> ButtonsAfterHover;
};
