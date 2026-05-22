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
        bool onOverlay; // is this in the overlay layer

        virtual void draw(float) = 0;
};
