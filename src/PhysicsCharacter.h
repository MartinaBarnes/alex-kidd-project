#pragma once
#include "PhysicsRect.h"
#include "AABB.h"
#include "Entity.h"
#include "PhysicsTileMap.h"
#include "raylib.h"

class PhysicsCharacter : public PhysicsRect {
    public:
        Vector2 velocity = { 0, 0 };
        bool onCeiling;
        bool onWall;
        bool onGround;
        bool inWater;
        bool inDeathPit;

        bool testCollision(float, PhysicsComponent*) override;
};
