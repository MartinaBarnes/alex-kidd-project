#pragma once

#include "Entity.h"
#include "Player.h"
#include "AABB.h"

class Player;

class Door : public Entity
{
    protected:
        Player* player;

    public:
        AABB aabb;
        bool isExit = false;

        Door(Vector2 pos, Player* player);

        void update(float delta);
};
