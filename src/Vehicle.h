#pragma once
#include "LivingEntity.h"
#include "Player.h"

class Player;
class Vehicle : public LivingEntity {
    public:
        Player* driver = NULL;

        virtual Vector2 getPosition() = 0;
        virtual Vector2 getVelocity() = 0;
};
