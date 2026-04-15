#pragma once
#include "PhysicsComponent.h"

class PhysicsHitbox : public PhysicsComponent {
    public:
        AABB aabb;
        bool active = true;

        bool isOnScreen(const AABB*) const override;
};
