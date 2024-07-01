#include "colors.hpp"

const Color ClickedGreen{189, 201, 94, 255};
const Color ClickedWhite{245, 245, 154, 255};
const Color White{234, 236, 211, 255};
const Color Green{122, 147, 101, 255};

Color SetClickedColor(int row, int column) {
    return (row + column) % 2 ? ClickedWhite : ClickedGreen;
}