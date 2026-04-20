#include "Onigiri.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "SceneManager.h"
#include "SceneFactory.h"
#include "ResourceManager.h"

void Onigiri::update(float dt) {
    if (touched) {
        delay += dt;
        if (delay < DELAY_TIME) {
            return;
        }
        RenderingServer::visible = false;
        if (delay < DELAY_TIME * 2) {
            return;
        }
        SceneManager::replace(SceneFactory::gameOver());
        return;
    }
    for (int i = 0; i < physics->colliders.size(); i++) {
        touched = true;
        delay = 0.0f;
        pausable = true;
        SceneManager::pause = true;
        StopMusicStream(*scene->music);
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
