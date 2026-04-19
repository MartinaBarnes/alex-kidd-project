#pragma once
#include "AABB.h"

/**
 * On screen object class.
 * Base for all game objects that interact with the culling system
 * for performance.
 */
class OnScreenObject {
    public:
        virtual bool isOnScreen() const = 0;
};
