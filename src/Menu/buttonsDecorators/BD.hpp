#pragma once
#include "../MenuButton.hpp"

template <typename T>
concept isAButton = std::is_base_of<MenuButton, T>::value;

template <isAButton T>
class ButtonStateDecorator : public T { 
    public:
    template <typename...Args>
        explicit ButtonStateDecorator(Args ...args): T(std::forward<Args>(args)...) {}

    void Draw() override {
        T::Draw(); 
        if (!T::isActive) DrawRectangleRounded(T::area, 0.2, 0, Fade(BLACK, 0.7f));
    }

};

template <isAButton T>
class ButtonColorDecorator : public T { 
    public:
    template <typename...Args>
        ButtonColorDecorator(Color BackgroundColor, Color TextColor, Args ...args): T(std::forward<Args>(args)...) {
            T::TextColor = TextColor;
            T::BackgroundColor = BackgroundColor;
        }
};

