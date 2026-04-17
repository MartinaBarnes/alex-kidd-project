#include "Scene.h"
#include "SceneManager.h"

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
    bool markedForDeletion = false;
    for (int i = 0; i < entities.size(); i++) {
        Entity* entity = entities[i];
        if (SceneManager::pause && !entity->pausable) {
            continue;
        }
        entity->update(dt);
        if (entity->markedForDeletion) {
            markedForDeletion = true;
        }
    }
    if (!markedForDeletion) {
        return;
    }
    int count = entities.size();
    for (int i = 0; i < count; i++) {
        Entity* entity = entities[i];
        if (!entity->markedForDeletion) {
            continue;
        }
        entities[i] = entities[count - 1];
        entities.pop_back();
        delete entity;
        count--;
        i--;
    }
}

Scene::~Scene() {
    for (int i = 0; i < entities.size(); i++) {
        delete entities[i];
    }
}
