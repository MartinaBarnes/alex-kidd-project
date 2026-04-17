#include "Scene.h"
#include "AABB.h"

#define GAME_WIDTH 256
#define GAME_HEIGHT 192

class SceneManager {
    public:
        static bool pause;
        static Scene* current;
        static AABB* workspace;

        static void replace(Scene*);
};
