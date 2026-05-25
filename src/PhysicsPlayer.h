#pragma once
#include "PhysicsCharacter.h"
#include "Player.h"

class Player;
class PhysicsPlayer : public PhysicsCharacter {
    public:
        Player* owner = NULL;
        bool isOnScreen() const override;
};
