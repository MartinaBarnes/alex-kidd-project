#pragma once
#include "RenderComponent.h"

class MapPreview : public RenderComponent {
    protected:
        const float MAP_ARROW_BLINK_TIME = 0.1f;
        bool mapArrowBlinked = false;
        float mapArrowBlinkTime = 0.0f;
    public:
        Vector2 position;
        Vector2 arrowPosition;
        float open = 0.0f;
        void draw(float) override;
};
