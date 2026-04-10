#include "Scene.h"

void Scene::push(Entity* entity) {
    entities.push_back(entity);
    entity->scene = this;
}

void Scene::pop(Entity* entity)
{
    int count = entities.size();
    for (int i = 0; i < count; i++) {
        if (entities[i] == entity) {
            entities[i] = entities[count - 1];
            entities.pop_back();
            entity->scene = nullptr;
            return;
        }
    }
}

void Scene::update(float dt) {
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(dt);
    }
}

Scene::~Scene() {
    for (int i = 0; i < entities.size(); i++) {
        delete entities[i];
    }
}
