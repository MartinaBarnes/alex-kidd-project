#include "Scene.h"

class SceneManager {
    public:
        static bool pause;
        static Scene* current;

        static void replace(Scene*);
};
