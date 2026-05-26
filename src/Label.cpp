#include "Label.h"
#include "ResourceManager.h"
#include <cmath>

void Label::draw(float _) {
    float x = position.x;
    float y = position.y;
    const char* str = text.c_str();
    int fontSize = 8;
    Font font = *ResourceManager::getFont("alex-kidd-in-miracle-world-sms");
    float size = std::round(MeasureTextEx(font, str, fontSize, 0).x);

    if (align == TEXTALIGN_RIGHT) {
        x -= size;
    } else if (align == TEXTALIGN_CENTER) {
        x += size / 2;
    }

    DrawTextEx(font, str, Vector2 { x, y }, fontSize, 0, WHITE);
}
