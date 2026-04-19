#pragma once
#include "PhysicsComponent.h"
#include "AABB.h"
#include <vector>

/**
 * Physics server class.
 * Handles all physics interactions.
 */
class PhysicsServer {
    public:
        static std::vector<PhysicsComponent*> components;
        static void push(PhysicsComponent*);
        static void pop(PhysicsComponent*);
        static void update(float);
};
