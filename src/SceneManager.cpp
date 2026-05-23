#include "SceneManager.h"
#include "SceneFactory.h"
#include "RenderingServer.h"

bool SceneManager::pause = false;
Scene* SceneManager::scene = NULL;
int SceneManager::queued = SCENE_NONE;
AABB* SceneManager::workspace = new AABB(-32, -32, GAME_WIDTH + 64, GAME_HEIGHT + 64);
