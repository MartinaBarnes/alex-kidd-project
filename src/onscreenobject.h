#pragma once
#include "aabb.h"

class OnScreenObject {
    public:
        virtual bool isOnScreen(const AABB*) const = 0;
};
