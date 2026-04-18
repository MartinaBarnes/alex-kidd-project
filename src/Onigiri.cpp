#include "Onigiri.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "ResourceManager.h"

void Onigiri::update(float dt) {
    for (int i = 0; i < physics->colliders.size(); i++) {
        // TODO: go to next level or game over for now
        return;
    }
}

Onigiri::Onigiri(Vector2 position) {
    physics = new PhysicsArea();
    physics->mask = LAYER_PLAYER;
    physics->aabb.position = position;
    physics->aabb.size = Vector2 { 16, 16 };
    PhysicsServer::push(physics);

    sprite = new Sprite();
    sprite->texture = ResourceManager::getTexture("items");
    sprite->frame = Rectangle { 0, 0, 16, 16 };
    sprite->position = position;
    RenderingServer::push(sprite);
}

Onigiri::~Onigiri() {
    PhysicsServer::pop(physics);
    delete physics;

    RenderingServer::pop(sprite);
    delete sprite;
}
