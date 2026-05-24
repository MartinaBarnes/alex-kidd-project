#pragma once
#include "PhysicsCharacter.h"

class PhysicsPlayer : public PhysicsCharacter {
    public:
        bool isOnScreen() const override;
};
