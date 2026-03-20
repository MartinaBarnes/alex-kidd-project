#include "Scene.h"

void Scene::update(float delta) {
    for (int i=0; i<entities.size(); i++) {
        entities[i]->update(delta);
    }
}
