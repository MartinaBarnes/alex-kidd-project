#include "Scene.h"
#include "AABB.h"

#define GAME_WIDTH 256
#define GAME_HEIGHT 192

/**
 * Scene manager class.
 * Keeps track of the current scene, whether the game is paused,
 * and the position of the object culling area.
 */
class SceneManager {
    public:
        static bool pause;
        static bool inPlayableLevel;
        static int queued;
        static Scene* scene;
        static AABB* workspace;
        static bool music;
};
