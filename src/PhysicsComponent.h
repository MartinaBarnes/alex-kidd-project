#pragma once
#include "OnScreenObject.h"
#include <vector>

#define LAYER_NONE 0
#define LAYER_WORLD 1
#define LAYER_PLAYER 2
#define LAYER_ENEMY 3
#define LAYER_BREAKABLE 4

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
