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
    const float MOVE_SPEED = 100.0f;
    const float GRAVITY = 70.0f;
    const float BOUNCE_FORCE = 50.0f;

    PhysicsPlayer* physics;
    PhysicsHitbox* hitbox;
    AnimatedSprite* sprite;

    void update(float delta) override;
    void onKilled() override;

    Pogostick();
    ~Pogostick();
};