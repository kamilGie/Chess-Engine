#pragma once
#include "../MenuButton.hpp"

template <typename T>
concept isADrawable = std::is_base_of<Drawable, T>::value;

template <isADrawable T>
class ButtonStateDecorator : public T { 
    public:
    template <typename...Args>
        ButtonStateDecorator(Args ...args): T(std::forward<Args>(args)...) {}

    void Draw() override {
        T::Draw(); 
        if (!T::isActive) DrawRectangleRounded(T::area, 0.2, 0, Fade(BLACK, 0.7f));
    }

};

