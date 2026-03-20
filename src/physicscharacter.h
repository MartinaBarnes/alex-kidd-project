#pragma once
#include "physicscomponent.h"
#include "aabb.h"
#include "raylib.h"

class PhysicsCharacter : public PhysicsComponent {
    public:
        AABB aabb;

        bool isOnScreen(const AABB*) const override;
        bool testCollision(PhysicsComponent*) override;
};
