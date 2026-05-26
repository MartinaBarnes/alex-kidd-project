#include "PurchaseOption.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "GameState.h"

void PurchaseOption::setPrice(int amount) {
    price = amount;
    label->text = std::to_string(amount);
}

void PurchaseOption::placeAt(Vector2 position) {
    physics->aabb.position = position;
    sprite->position = position;
    label->position = position;
    label->position.x += sprite->frame.width;
    label->position.y -= 10.0f;
}

void PurchaseOption::onPurchase() {
    if (GameState::baums < price) {
        return;
    }
    dialog->thankYou();
    markedForDeletion = true;
    GameState::shop[slot] = false;
    GameState::baums -= price;
    if (item == BUY_LIFE) {
        GameState::lives++;
        return;
    }
}

void PurchaseOption::update(float _) {
    if (physics->colliders.empty()) {
        return;
    }
    onPurchase();
}

PurchaseOption::PurchaseOption() {
    sprite = new Sprite();
    RenderingServer::push(sprite);

    label = new Label();
    label->align = TEXTALIGN_RIGHT;
    RenderingServer::push(label);

    physics = new PhysicsArea();
    physics->aabb.size = Vector2 { 16, 16 };
    //physics->layer = LAYER_WORLD;
    physics->mask = LAYER_PLAYER;
    PhysicsServer::push(physics);
}

PurchaseOption::~PurchaseOption() {
    RenderingServer::pop(sprite);
    delete sprite;

    RenderingServer::pop(label);
    delete label;

    PhysicsServer::pop(physics);
    delete physics;
}
