#pragma once
#include "RenderComponent.h"
#include <string>

enum TextAlign {
    TEXTALIGN_LEFT,
    TEXTALIGN_RIGHT,
    TEXTALIGN_CENTER
};

class Label : public RenderComponent {
    public:
        TextAlign align = TEXTALIGN_LEFT;
        std::string text = "";
        Vector2 position = Vector2 { 0 };

        void draw(float) override;
};
