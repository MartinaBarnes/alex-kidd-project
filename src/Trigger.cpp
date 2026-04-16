#include "Trigger.h"
#include "PhysicsServer.h"
#include "PhysicsCharacter.h"

void Trigger::update(float _) {
    for (int i = 0; i < physics->colliders.size(); i++) {
        if (PhysicsCharacter* character = dynamic_cast<PhysicsCharacter*>(physics->colliders[i])) {
            onTouch();
            return;
        }
    }
}

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
