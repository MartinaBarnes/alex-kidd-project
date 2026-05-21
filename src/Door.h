#pragma once

#include "Entity.h"
#include "Player.h"
#include "AABB.h"

class Door : public Entity
{
    protected:
        AABB aabb;
        Player* player;

    public:
        bool isExit = false;

        Door(Vector2 pos, Player* player);

        void update(float delta);
};