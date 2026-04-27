#include "PhysicsServer.h"
#include "SceneManager.h"

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

void PhysicsServer::update(float dt)
{
    // count how many physics objects are interacting on a frame
    std::vector<PhysicsComponent*> components = {};
    for (int i=0; i<PhysicsServer::components.size(); i++) {
        PhysicsComponent* component = PhysicsServer::components[i];
        if (SceneManager::pause && !component->pausable) {
            continue;
        }
        component->awake = component->enabled && component->isOnScreen();
        component->resetCollisionData();
        if (!component->awake) {
            continue;
        }
        components.push_back(component);
    }

    // run physics interactions
    for (int i=0; i<components.size(); i++) {
        PhysicsComponent* collider = components[i];
        for (int j=0; j<components.size(); j++) {
            if (i == j) {
                continue; // do not collide with self
            }
            PhysicsComponent* collided = components[j];
            if (!collided->enabled || (collider->mask & collided->layer) == 0 || !collider->testCollision(dt, collided)) {
                continue; // filter the physics layers based on the mask
            }
            collider->isColliding = true;
            collider->colliders.push_back(collided);
            collider->onCollision(collided);
            if (!collider->enabled) {
                collider->awake = false;
                break;
            }
        }
    }
};
