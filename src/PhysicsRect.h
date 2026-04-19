#pragma once
#include "PhysicsComponent.h"

class PhysicsRect : public PhysicsComponent {
    public:
        AABB aabb;

        bool isOnScreen() const override;
        bool testCollision(float, PhysicsComponent*) override;
        void onCollision(PhysicsComponent*) override;
};
