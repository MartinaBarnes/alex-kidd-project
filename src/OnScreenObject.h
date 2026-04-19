#pragma once
#include "AABB.h"

class OnScreenObject {
    public:
        virtual bool isOnScreen() const = 0;
};
