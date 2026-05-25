#include "ItemPickup.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "GameState.h"
#include "Pogostick.h"

void ItemPickup::placeAt(Vector2 position) {
    physics->aabb.position = position;
    sprite->position = position;
}

void ItemPickup::onPickup(Player* player) {
    markedForDeletion = true;
    PlaySound(*ResourceManager::getSound("item_pickup"));
    if (item == ITEM_LIFE) {
        GameState::lives++;
        return;
    }
    if (item == ITEM_POGOSTICK) {
        Pogostick* pogostick = new Pogostick();
        pogostick->physics->aabb.position.x = player->physics->aabb.position.x;
        pogostick->physics->aabb.position.y = player->physics->aabb.position.y - 11.0f;
        pogostick->driver = player;
        player->vehicle = pogostick;
        scene->push(pogostick);
    }
}

void ItemPickup::update(float _) {
    if (physics->colliders.empty()) {
        return;
    }
    onPickup(((PhysicsPlayer*)physics->colliders[0])->owner);
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
