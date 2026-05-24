#include "ItemPickup.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "GameState.h"

void ItemPickup::placeAt(Vector2 position) {
    physics->aabb.position = position;
    sprite->position = position;
}

void ItemPickup::onPickup() {
    markedForDeletion = true;
    if (item == ITEM_LIFE) {
        GameState::lives++;
        return;
    }
    // TODO: give pogo stick
}

void ItemPickup::update(float _) {
    if (physics->colliders.empty()) {
        return;
    }
    onPickup();
}

ItemPickup::ItemPickup() {
    sprite = new Sprite();
    RenderingServer::push(sprite);

    physics = new PhysicsArea();
    physics->aabb.size = Vector2 { 16, 16 };
    physics->layer = LAYER_WORLD;
    physics->mask = LAYER_PLAYER;
    PhysicsServer::push(physics);
}

ItemPickup::~ItemPickup() {
    RenderingServer::pop(sprite);
    delete sprite;

    PhysicsServer::pop(physics);
    delete physics;
}
