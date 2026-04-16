#pragma once
#include "OnScreenObject.h"
#include <vector>

#define LAYER_NONE 0
#define LAYER_WORLD 1
#define LAYER_PLAYER 2
#define LAYER_ENEMY 4
#define LAYER_BREAKABLE 8
#define LAYER_BOUNDS 16
#define LAYER_TRIGGER 32

class PhysicsComponent : public OnScreenObject {
    public:
        bool enabled = true;
        bool awake;
        int layer;
        int mask;
        bool isColliding;
        std::vector<PhysicsComponent*> colliders = {};

        virtual bool testCollision(float, PhysicsComponent*) { return false; };
};
