#pragma once
#include "PhysicsComponent.h"

class PhysicsSolid : public PhysicsComponent {
    public:
        AABB aabb;

        bool isOnScreen(const AABB*) const override;
};
