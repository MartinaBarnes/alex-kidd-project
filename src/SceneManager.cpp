#include "SceneManager.h"

bool SceneManager::pause = false;
Scene* SceneManager::current = NULL;
AABB* SceneManager::workspace = new AABB(0, 0, GAME_WIDTH + 32, GAME_HEIGHT + 32);

void SceneManager::replace(Scene* scene) {
    if (SceneManager::current != NULL) {
        delete SceneManager::current;
    }
    SceneManager::current = scene;
}
