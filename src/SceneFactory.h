#include "Scene.h"
#include "WanderingEnemy.h"

enum {
    SCENE_NONE,
    SCENE_INTRO,
    SCENE_TITLE,
    SCENE_PREVIEW1,
    SCENE_LEVEL1,
    SCENE_PREVIEW2,
    SCENE_LEVEL2,
    SCENE_GAMEOVER,
    SCENE_SHOP
};

/**
 * Scene factory class.
 * Static helper class to create scene instances.
 */
class SceneFactory {
    public:
        static Scene* intro(); // instances the game intro
        static Scene* title(); // instances the title screen
        static Scene* preview1(); // instances the intro to level 1
        static Scene* level1(); // instances the level 1
        static Scene* preview2(); // instances the intro to level 2
        static Scene* level2(); // instances the level 2
        static Scene* gameOver(); // instances the game over screen
        static Scene* shop(); // instances the level 2 shop
        static WanderingEnemy* scorpion(); // instances a scorpion
        static WanderingEnemy* kaicho(); // instances a monster bird
};
