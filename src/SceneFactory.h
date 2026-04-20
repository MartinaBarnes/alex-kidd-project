#include "Scene.h"

/**
 * Scene factory class.
 * Static helper class to create scene instances.
 */
class SceneFactory {
    public:
        static Scene* title(); // instances the title screen
        static Scene* intro1(); // instances the intro to level 1
        static Scene* level1(); // instances the level 1
        static Scene* gameOver(); // instances the game over screen
};
