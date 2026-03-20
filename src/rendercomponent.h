#pragma once
#include "OnScreenObject.h"

class RenderComponent : public OnScreenObject {
    public:
        bool visible;
        virtual void draw() = 0;
};
