#include "PhysicsServer.h"
#include "raylib.h"
#include <vector>

std::vector<PhysicsComponent*> PhysicsServer::components = {};

void PhysicsServer::push(PhysicsComponent* component)
{
    PhysicsServer::components.push_back(component);
}

void PhysicsServer::pop(PhysicsComponent* component)
{
    int count = PhysicsServer::components.size();
    for (int i=0; i<count; i++) {
        if (PhysicsServer::components[i] == component) {
            PhysicsServer::components[i] = PhysicsServer::components[count - 1];
            PhysicsServer::components.pop_back();
            return;
        }
    }
}

void PhysicsServer::update(float dt, const AABB* viewport)
{
    std::vector<PhysicsComponent*> components = {};
    for (int i=0; i<PhysicsServer::components.size(); i++) {
        PhysicsComponent* component = PhysicsServer::components[i];
        component->awake = component->isOnScreen(viewport);
        component->isColliding = false;
        component->colliders.resize(0);
        if (!component->awake) {
            continue;
        }
        components.push_back(component);
    }
    for (int i=0; i<components.size(); i++) {
        PhysicsComponent* collider = components[i];
        for (int j=0; j<components.size(); j++) {
            if (i == j) {
                continue;
            }
            PhysicsComponent* collided = components[j];
            if ((collider->mask & collided->layer) == 0 || !collider->testCollision(dt, collided)) {
                continue;
            }
            collider->isColliding = true;
            collider->colliders.push_back(collided);
            collider->onCollision(collided);
        }
    }
};
