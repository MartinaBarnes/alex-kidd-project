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

    public:
        const float MOVE_SPEED = 80.0f;
        const float GRAVITY = 140.0f;
        const float BOUNCE_FORCE = 100.0f;

        PhysicsPlayer* physics;
        PhysicsHitbox* hitbox;
        AnimatedSprite* sprite;

        Vector2 getPosition() override;
        Vector2 getVelocity() override;
        void update(float delta) override;
        void onKilled() override;

        Pogostick();
        ~Pogostick();
};
