#include "SceneManager.h"

bool SceneManager::pause = false;
Scene* SceneManager::current = NULL;
AABB* SceneManager::workspace = new AABB(-32, -32, GAME_WIDTH + 64, GAME_HEIGHT + 64);

void SceneManager::replace(Scene* scene) {
    if (SceneManager::current != NULL) {
        delete SceneManager::current;
    }
    SceneManager::current = scene;
}
