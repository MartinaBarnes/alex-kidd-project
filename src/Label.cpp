#include "Label.h"
#include <cmath>

void Label::draw(float _) {
    int x = (int)position.x;
    int y = (int)position.y;
    const char* str = text.c_str();
    int size = (int)std::round(MeasureText(str, 10));

    if (align == TEXTALIGN_RIGHT) {
        x -= size;
    } else if (align == TEXTALIGN_CENTER) {
        x += size / 2;
    }

    DrawText(str, x, y, 10, WHITE);
}
