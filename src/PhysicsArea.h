#pragma once
#include "PhysicsComponent.h"

class PhysicsArea : public PhysicsComponent {
    public:
        AABB aabb;

        bool isOnScreen(const AABB*) const override;
};
