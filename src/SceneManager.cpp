#include "SceneManager.h"
#include "RenderingServer.h"

bool SceneManager::pause = false;
Scene* SceneManager::current = NULL;
Scene* SceneManager::queued = NULL;
AABB* SceneManager::workspace = new AABB(-32, -32, GAME_WIDTH + 64, GAME_HEIGHT + 64);
