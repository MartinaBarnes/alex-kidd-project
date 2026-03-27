#pragma once
#include "OnScreenObject.h"
#include <vector>

class PhysicsComponent : public OnScreenObject {
    public:
        bool awake;
        int layer;
        int mask;
        bool isColliding;
        std::vector<PhysicsComponent*> colliders = {};

        virtual bool testCollision(float, PhysicsComponent*) { return false; };
        virtual void onCollision(PhysicsComponent*) {};
};
