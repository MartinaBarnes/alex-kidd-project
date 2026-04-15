#pragma once
#include "OnScreenObject.h"

class RenderComponent : public OnScreenObject {
    public:
        bool enabled = true;
        bool visible;
        virtual void draw(float) = 0;
};
