#pragma once
#include "PhysicsRect.h"
#include "AABB.h"
#include "Entity.h"
#include "PhysicsTileMap.h"
#include "raylib.h"

/**
 * Physics character class.
 * A physics object for characters, which have a velocity and
 * can collide with their surroundings.
 */
class PhysicsCharacter : public PhysicsRect {
    public:
        Vector2 velocity = { 0, 0 }; // proper way to move a character
        bool onCeiling;
        bool onWall;
        bool onGround;
        bool inWater;
        bool inDeathPit;

        bool testCollision(float, PhysicsComponent*) override;
};
