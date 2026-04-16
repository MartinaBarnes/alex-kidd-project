#include "Trigger.h"
#include "PhysicsServer.h"

Trigger::Trigger(Vector2 position, Vector2 size) {
    physics = new PhysicsArea();
    physics->layer = LAYER_TRIGGER;
    physics->mask = LAYER_PLAYER;
    physics->aabb.position = position;
    physics->aabb.size = size;
    PhysicsServer::push(physics);
}

Trigger::~Trigger() {
    PhysicsServer::pop(physics);
    delete physics;
}
