#include "PurchaseOption.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"

void PurchaseOption::update(float _) {
    // TODO: check for collision and purchase
}

PurchaseOption::PurchaseOption() {
    sprite = new Sprite();
    PhysicsServer::push(sprite);

    label = new Label();
    RenderingServer::push(label);

    physics = new PhysicsArea();
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
