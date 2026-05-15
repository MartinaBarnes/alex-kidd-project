#pragma once

#include "Entity.h"
#include "PhysicsHitbox.h"
#include "AnimatedSprite.h"
#include "Player.h"

enum DoorState
{
    IDLE,
    ENTERING,
    INSIDE_WAIT,
    INSIDE
};

class Door : public Entity
{
protected:

    PhysicsHitbox* hitbox;
    AnimatedSprite* sprite;

    Player* player;

    DoorState state = IDLE;

    float timer = 0.0f;

public:

    Door(Vector2 pos, Player* player);

    ~Door();

    void update(float delta);
};