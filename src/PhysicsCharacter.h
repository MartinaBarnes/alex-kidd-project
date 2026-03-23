#pragma once
#include "PhysicsComponent.h"
#include "AABB.h"
#include "Entity.h"
#include "PhysicsTileMap.h"
#include "raylib.h"

class PhysicsCharacter : public PhysicsComponent {
    public:
        AABB aabb;
        Vector2 velocity = { 0, 0 };
        bool onCeiling;
        bool onWall;
        bool onGround;
        Entity* owner;

        bool isOnScreen(const AABB*) const override;
        bool testCollision(PhysicsComponent*) override;
};
