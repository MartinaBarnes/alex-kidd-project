#pragma once
#include "onscreenobject.h"
#include <vector>

class PhysicsComponent : public OnScreenObject {
    public:
        bool awake;
        int layer;
        int mask;
        std::vector<PhysicsComponent*> colliders = {};

        virtual bool testCollision(PhysicsComponent*) { return false; };
        virtual void onCollision(PhysicsComponent*) {};
};
