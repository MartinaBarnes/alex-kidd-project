#pragma once
#include "OnScreenObject.h"
#include <vector>

#define LAYER_NONE      0
#define LAYER_WORLD     1
#define LAYER_PLAYER    2
#define LAYER_ENEMY     4
#define LAYER_BOUNDS    8
#define LAYER_TRIGGER   16
#define LAYER_BREAKABLE 32

/**
 * Physics component class.
 * Base for all physics objects that interact with the PhysicsServer.
 */
class PhysicsComponent : public OnScreenObject {
    public:
        bool pausable = false;
        bool enabled = true;
        bool awake; // whether the object is enabled and on screen
        int layer; // what physics layer this object belongs to
        int mask; // what layers of physics object this collides with
        bool isColliding; // did it collide in the last frame
        std::vector<PhysicsComponent*> colliders = {}; // objects collided in the last frame

        virtual void resetCollisionData() {
            isColliding = false;
            colliders.resize(0);
        };
        virtual bool testCollision(float, PhysicsComponent*) { return false; };
        virtual void onCollision(PhysicsComponent*) {};
};
