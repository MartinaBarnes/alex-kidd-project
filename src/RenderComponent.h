#pragma once
#include "OnScreenObject.h"

/**
 * Render component class.
 * Base for all drawable objects.
 */
class RenderComponent : public OnScreenObject {
    public:
        bool pausable = false;
        bool enabled = true;
        bool visible; // is it enabled and on screen

        virtual void draw(float) = 0;
};
