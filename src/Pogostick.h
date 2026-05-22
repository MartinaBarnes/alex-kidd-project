#pragma once
#include "Vehicle.h"
#include "PhysicsCharacter.h"
#include "PhysicsHitbox.h"
#include "AnimatedSprite.h"
#include"Player.h"

class Pogostick : public Vehicle
{
protected:
    float direction = DIRECTION_RIGHT;
    bool bouncing = false;

public:
    const float MOVE_SPEED = 180.0f;
    const float GRAVITY = 900.0f;
    const float BOUNCE_FORCE = 350.0f;
    const float MAX_FALL_SPEED = 700.0f;

    PhysicsCharacter* physics;
    PhysicsHitbox* hitbox;
    AnimatedSprite* sprite;

    void update(float delta);

    Pogostick();
    ~Pogostick();
};