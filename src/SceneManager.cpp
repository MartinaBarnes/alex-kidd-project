#include "SceneManager.h"

bool SceneManager::pause = false;
Scene* SceneManager::current = NULL;

void SceneManager::replace(Scene* scene) {
    if (SceneManager::current != NULL) {
        delete SceneManager::current;
    }
    SceneManager::current = scene;
}
