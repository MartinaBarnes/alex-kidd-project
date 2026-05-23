#pragma once
#include "PhysicsComponent.h"

/**
 * Physics rectangle class.
 * A physics object with an axis aligned bounding box.
 */
class PhysicsRect : public PhysicsComponent {
    public:
        bool always = false;
        AABB aabb;

        bool isOnScreen() const override;
        bool testCollision(float, PhysicsComponent*) override;
        void onCollision(PhysicsComponent*) override;
};
