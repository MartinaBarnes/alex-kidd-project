#include "SceneFactory.h"
#include "PhysicsTileMap.h"
#include "RenderTileMap.h"
#include "RenderingServer.h"
#include "ResourceManager.h"
#include "TileAnimationController.h"
#include "TileMap.h"
#include "Player.h"
#include "CameraController.h"
#include "Breakable.h"
#include "Onigiri.h"
#include "GameState.h"
#include "GameOverController.h"
#include "MapTransitionController.h"
#include "TitleSplashController.h"
#include "IntroSplashController.h"
#include "BaumDrop.h"
#include "BaumPickup.h"
#include "Door.h"
#include "CoinCounter.h"
#include "PurchaseOption.h"

Scene* SceneFactory::intro() {
    Scene* scene = new Scene();
    scene->background = BLACK;
    scene->push(new IntroSplashController());
    return scene;
}

Scene* SceneFactory::title() {
    // initialize scene
    Scene* scene = new Scene();
    scene->background = Color { 255, 255, 170, 255 };

    // instance screen
    scene->push(new TitleSplashController());

    // play music
    Sound* jingle = ResourceManager::getSound("title_screen");
    SetSoundVolume(*jingle, 0.5f);
    PlaySound(*jingle);

    return scene;
}

Scene* SceneFactory::preview1() {
    // initialize scene
    Scene* scene = new Scene();
    scene->background = BLACK;

    // instance screen
    MapTransitionController* transition = new MapTransitionController();
    transition->preview->arrowPosition = Vector2 { 58, 53 }; // 140, 72
    scene->push(transition);

    // play music
    Sound* jingle = ResourceManager::getSound("level_start");
    SetSoundVolume(*jingle, 0.5f);
    PlaySound(*jingle);

    return scene;
}

Scene* SceneFactory::level1() {
    // level data definition
    Texture2D* atlas = ResourceManager::getTexture("tiles");

    enum {
        TILE_NONE,
        TILE_GRASS,
        TILE_TGRASS,
        TILE_BORB,
        TILE_RORB,
        TILE_TREE0,
        TILE_TREE1,
        TILE_TREE2,
        TILE_CLD0,
        TILE_CLD1,
        TILE_LAVA,
        TILE_LAVA0,
        TILE_LAVA1,
        TILE_LAVA2,
        TILE_LAVA3,
        TILE_BOXITEM,
        TILE_BOXSTUN,
        TILE_TMPLT0L,
        TILE_TMPLT1L,
        TILE_TMPLT0R,
        TILE_TMPLT1R,
        TILE_TMPLS0L,
        TILE_TMPLS1L,
        TILE_TMPLS0R,
        TILE_TMPLS1R,
        TILE_TMPLC0,
        TILE_TMPLC1,
        TILE_TMPLC2,
        TILE_TMPLC3,
        TILE_TMPLC4,
        TILE_TMPLC5,
        TILE_TMPLC6,
        TILE_TMPLC7,
        TILE_TMPLC8,
        TILE_TMPLG,
    };

    Rectangle tiles[128] = {
        Rectangle { 0 },
        Rectangle { 0, 48, 16, 16 },
        Rectangle { 0, 32, 16, 16 },
        Rectangle { 96, 32, 16, 16 },
        Rectangle { 80, 0, 16, 16 },
        Rectangle { 176, 0, 16, 16 },
        Rectangle { 176, 16, 16, 16 },
        Rectangle { 176, 32, 16, 16 },
        Rectangle { 112, 0, 16, 16 },
        Rectangle { 128, 0, 16, 16 },
        Rectangle { 112, 48, 16, 16 },
        Rectangle { 128, 32, 16, 16 },
        Rectangle { 144, 32, 16, 16 },
        Rectangle { 160, 32, 16, 16 },
        Rectangle { 112, 32, 16, 16 },
        Rectangle { 16, 0, 16, 16 },
        Rectangle { 16, 16, 16, 16 },
        Rectangle { 192, 0, 16, 16 },
        Rectangle { 192, 16, 16, 16 },
        Rectangle { 208, 0, 16, 16 },
        Rectangle { 208, 16, 16, 16 },
        Rectangle { 192, 32, 16, 16 },
        Rectangle { 192, 48, 16, 16 },
        Rectangle { 208, 32, 16, 16 },
        Rectangle { 208, 48, 16, 16 },
        Rectangle { 224, 0, 16, 16 },
        Rectangle { 240, 0, 16, 16 },
        Rectangle { 224, 16, 16, 16 },
        Rectangle { 240, 16, 16, 16 },
        Rectangle { 224, 32, 16, 16 },
        Rectangle { 240, 32, 16, 16 },
        Rectangle { 224, 48, 16, 16 },
        Rectangle { 240, 48, 16, 16 },
        Rectangle { 16, 32, 16, 16 }
    };

    short map[TILEMAP_HEIGHT][TILEMAP_WIDTH] = {
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  9   },
        {   8,  9,  0,  0,  0,  0,  0,  0,  15, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0   },
        {   0,  0,  0,  0,  15, 0,  0,  0,  0,  0,  0,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  3,  3,  0,  8,  9,  0,  0,  0,  0,  4,  0,  3,  0,  3,  3,  0,  0,  0,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  9,  0,  0,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  9,  0,  0,  0   },
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,  0,  3,  0,  0,  0,  3,  3,  0,  0,  0,  3,  0,  0,  0,  0,  0,  0,  5,  15, 3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0   },
        {   5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  16, 15, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  3,  3,  0,  0,  0,  0,  0,  0,  4,  5,  0,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  17, 19, 0,  0,  6,  0   },
        {   6,  5,  0,  0,  0,  0,  0,  0,  5,  0,  0,  0,  0,  0,  3,  15, 0,  0,  0,  0,  0,  4,  3,  0,  0,  0,  0,  0,  0,  0,  5,  0,  0,  6,  4,  3,  0,  0,  0,  3,  15, 0,  3,  6,  0,  3,  6,  0,  3,  5,  0,  0,  0,  0,  0,  0,  4,  4,  4,  4,  4,  4,  4,  5,  0,  5,  0,  0,  0,  0,  0,  0 , 18, 20, 0,  0,  6,  0   },
        {   6,  6,  0,  0,  0,  0,  0,  0,  6,  0,  3,  3,  0,  5,  3,  15, 0,  0,  0,  3,  0,  3,  3,  0,  0,  0,  0,  0,  0,  4,  6,  0,  0,  6,  3,  3,  0,  0,  0,  3,  3,  0,  0,  6,  0,  4,  6,  0,  0,  6,  4,  0,  0,  0,  0,  0,  3,  3,  3,  3,  3,  3,  3,  6,  5,  6,  0,  0,  0,  0,  0,  21, 25, 26, 23, 0,  6,  5   },
        {   6,  6,  0,  0,  0,  0,  3,  3,  6,  0,  3,  3,  0,  6,  3,  4,  0,  0,  0,  3,  0,  0,  0,  0,  3,  0,  0,  0,  0,  5,  6,  0,  3,  7,  3,  16, 0,  3,  0,  3,  15, 0,  0,  6,  0,  0,  7,  0,  0,  6,  0,  0,  0,  0,  0,  3,  3,  0,  0,  0,  0,  0,  3,  6,  6,  6,  0,  0,  0,  0,  0,  22, 27, 28, 24, 0,  7,  6   },
        {   7,  7,  3,  3,  0,  0,  3,  16, 7,  0,  16, 4,  0,  6,  3,  16, 0,  15, 0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  6,  0,  4,  7,  3,  4,  0,  0,  0,  0,  0,  0,  0,  7,  0,  0,  7,  0,  0,  7,  0,  0,  0,  0,  3,  3,  3,  0,  15, 15, 15, 0,  4,  7,  6,  7,  0,  0,  0,  0,  0,  22, 29, 30, 24, 0,  7,  6   },
        {   7,  7,  3,  3,  0,  0,  3,  3,  7,  0,  3,  4,  0,  7,  4,  3,  0,  0,  0,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,  0,  0,  7,  3,  3,  0,  0,  0,  0,  0,  0,  0,  7,  0,  0,  7,  0,  0,  7,  0,  0,  0,  3,  3,  3,  4,  0,  0,  0,  0,  0,  4,  7,  7,  7,  0,  0,  0,  0,  0,  22, 31, 32, 24, 0,  7,  7   },
        {   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  20, 20, 20, 20, 2,  2,  2,  2,  2,  2,  2,  2,  20, 20, 20, 20, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  33, 33, 33, 33, 2,  2,  2   },
        {   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  10, 10, 10, 10, 1,  1,  1,  1,  1,  1,  1,  1,  10, 10, 10, 10, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   }
    };

    short physics[TILEMAP_HEIGHT][TILEMAP_WIDTH] = {
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  1,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  1,  1,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  1,  1,  0,  0,  0,  1,  1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1,  0,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  1,  1,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  1   },
        {   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  3,  3,  3,  1,  1,  1,  1,  1,  1,  1,  1,  3,  3,  3,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   },
    };

    Particles defaultParticles = Particles{ ResourceManager::getTexture("tiles"), { Rectangle { 112, 16, 7, 7 }, Rectangle { 120, 16, 7, 7 } } };
    std::map<int, Breakable*> breakables;
    breakables[TILE_BOXITEM] = new BaumDrop(defaultParticles);
    breakables[TILE_BOXSTUN] = new Breakable(defaultParticles);
    breakables[TILE_BORB] = new Breakable(Particles { ResourceManager::getTexture("tiles"), { Rectangle { 112, 24, 8, 8 }, Rectangle { 120, 24, 8, 8 } } });

    // initialize scene
    Scene* scene = new Scene();
    scene->background = Color { 0, 0, 255, 255 };
    scene->music = ResourceManager::getMusic("main_theme");

    // initialize tile map
    TileMap* tileMap = new TileMap();
    tileMap->render->texture = atlas;
    tileMap->render->setTileSet(tiles);
    tileMap->render->setTileMap(map);
    tileMap->physics->setTileMap(physics);
    tileMap->breakables = breakables;
    scene->push(tileMap);

    // animated lava tiles
    scene->push(new TileAnimationController(
        tileMap,
        { TILE_LAVA0, TILE_LAVA1, TILE_LAVA2, TILE_LAVA3 },
        {
            TileCoords { 24, 10 }, TileCoords { 25, 10 }, TileCoords { 26, 10 }, TileCoords { 27, 10 },
            TileCoords { 36, 10 }, TileCoords { 37, 10 }, TileCoords { 38, 10 }, TileCoords { 39, 10 }
        }
    ));

    // player
    Player* player = new Player();
	player->tileMap = tileMap;
	player->physics->aabb.position.x = 10.0f;
	player->physics->aabb.position.y = 136.0f + 8.0f;
	scene->push(player);

	// camera controller
	CameraController* cameraController = new CameraController();
	cameraController->player = player;
	cameraController->mode = CAM_RIGHT;
	cameraController->limits.x = 992;
	scene->push(cameraController);

    // scorpions
    WanderingEnemy* scorpion0 = SceneFactory::scorpion();
    scorpion0->physics->aabb.position = Vector2 { 62 * TILE_SIZE, 4 * TILE_SIZE + 2 };
    scorpion0->direction = -1;
    scorpion0->wander_distance = 6 * TILE_SIZE;
    scene->push(scorpion0);

    WanderingEnemy* scorpion1 = SceneFactory::scorpion();
    scorpion1->physics->aabb.position = Vector2 { 52 * TILE_SIZE, 10 * TILE_SIZE - 5 };
    scorpion1->direction = -1;
    scorpion1->wander_distance = 10 * TILE_SIZE;
    scene->push(scorpion1);

	// onigiri
	scene->push(new Onigiri(Vector2 { 75 * TILE_SIZE + 4, 7 * TILE_SIZE }));

	// create tall grass only tilemap
	TileMap* grass = new TileMap();
	grass->render->texture = atlas;
	grass->render->setTileSet(tiles);
	for (int x = 0; x <= 76; x++) {
	    if ((x >= 24 && x <= 27) || (x >= 36 && x <= 39)) {
			continue;
		}
	    grass->render->map[x][10] = TILE_TGRASS;
	}
	grass->physics->layer = 0;
	grass->physics->mask = 0;
	scene->push(grass);

    // play music
    SetMusicVolume(*scene->music, 0.5f);
    PlayMusicStream(*scene->music);

    // first level -- reset game state
    GameState::reset();

    return scene;
}

Scene* SceneFactory::preview2() {
    // initialize scene
    Scene* scene = new Scene();
    scene->background = BLACK;

    // instance screen
    MapTransitionController* transition = new MapTransitionController();
    transition->toLevel2 = true;
    transition->preview->arrowPosition = Vector2 { 80, 44 };
    scene->push(transition);

    // play music
    Sound* jingle = ResourceManager::getSound("level_start");
    SetSoundVolume(*jingle, 0.5f);
    PlaySound(*jingle);

    return scene;
}

Scene* SceneFactory::level2() {
    // level data definition
    Texture2D* atlas = ResourceManager::getTexture("tiles");

    enum {
        TILE_NONE,
        TILE_GRASS,
        TILE_GROCK,
        TILE_YROCK,
        TILE_CLD0,
        TILE_CLD1,
        TILE_QSND,
        TILE_QSND0,
        TILE_QSND1,
        TILE_QSND2,
        TILE_QSND3,
        TILE_BOXITEM,
        TILE_BOXSTUN,
        TILE_BLDTL0,
        TILE_BLDTC0,
        TILE_BLDTR0,
        TILE_BLDTL1,
        TILE_BLDTL2,
        TILE_BLDTC1,
        TILE_BLDTR1,
        TILE_BLDTR2,
        TILE_BLDSL,
        TILE_BLDSR,
        TILE_DOOR0,
        TILE_DOOR1,
        TILE_DOOR2,
        TILE_DOOR3,
        TILE_DOOR4,
        TILE_DOOR5,
        TILE_SHOPL0,
        TILE_SHOPR0,
        TILE_SHOPL1,
        TILE_SHOPR1,
        TILE_CITY0,
        TILE_CITY1,
        TILE_CITY2,
        TILE_CITY3,
        TILE_CITY4,
        TILE_CITY5,
        TILE_CITY6,
        TILE_CITY7,
        TILE_CITY8,
        TILE_CITY9,
        TILE_CITY10,
        TILE_CITY11,
        TILE_CITY12,
        TILE_CITY13,
        TILE_CITY14,
        TILE_CITY15,
        TILE_CITY16,
        TILE_CITY17,
        TILE_CITY18,
        TILE_CITY19,
        TILE_CITY20,
        TILE_CITY21,
        TILE_CITY22,
        TILE_CITY23,
        TILE_MNT0,
        TILE_MNT1,
        TILE_MNT2,
        TILE_MNT3,
        TILE_MNT4,
        TILE_MNT5,
        TILE_MNT6,
        TILE_MNT7,
        TILE_MNT8,
        TILE_MNT9,
        TILE_MNT10,
        TILE_MNT11,
        TILE_BOXQST,
        TILE_DOOR6
    };

    Rectangle tiles[128] = {
        Rectangle { 0 },
        Rectangle { 0, 48, 16, 16 },
        Rectangle { 96, 48, 16, 16 },
        Rectangle { 96, 0, 16, 16 },
        Rectangle { 112, 0, 16, 16 },
        Rectangle { 128, 0, 16, 16 },
        Rectangle { 144, 48, 16, 16 },
        Rectangle { 112, 64, 16, 16 },
        Rectangle { 128, 64, 16, 16 },
        Rectangle { 144, 64, 16, 16 },
        Rectangle { 160, 64, 16, 16 },
        Rectangle { 16, 0, 16, 16 },
        Rectangle { 16, 16, 16, 16 },
        Rectangle { 0, 64, 16, 16 },
        Rectangle { 16, 64, 16, 16 },
        Rectangle { 32, 64, 16, 16 },
        Rectangle { 0, 80, 16, 16 },
        Rectangle { 16, 80, 16, 16 },
        Rectangle { 32, 80, 16, 16 },
        Rectangle { 48, 80, 16, 16 },
        Rectangle { 64, 80, 16, 16 },
        Rectangle { 0, 112, 16, 16 },
        Rectangle { 64, 112, 16, 16 },
        Rectangle { 16, 96, 16, 16 },
        Rectangle { 32, 96, 16, 16 },
        Rectangle { 48, 96, 16, 16 },
        Rectangle { 16, 112, 16, 16 },
        Rectangle { 32, 112, 16, 16 },
        Rectangle { 48, 112, 16, 16 },
        Rectangle { 80, 96, 16, 16 },
        Rectangle { 96, 96, 16, 16 },
        Rectangle { 80, 112, 16, 16 },
        Rectangle { 96, 112, 16, 16 },
        Rectangle { 112, 80, 16, 16 },
        Rectangle { 128, 80, 16, 16 },
        Rectangle { 144, 80, 16, 16 },
        Rectangle { 160, 80, 16, 16 },
        Rectangle { 176, 80, 16, 16 },
        Rectangle { 192, 80, 16, 16 },
        Rectangle { 208, 80, 16, 16 },
        Rectangle { 224, 80, 16, 16 },
        Rectangle { 240, 80, 16, 16 },
        Rectangle { 112, 96, 16, 16 },
        Rectangle { 128, 96, 16, 16 },
        Rectangle { 144, 96, 16, 16 },
        Rectangle { 160, 96, 16, 16 },
        Rectangle { 176, 96, 16, 16 },
        Rectangle { 192, 96, 16, 16 },
        Rectangle { 208, 96, 16, 16 },
        Rectangle { 224, 96, 16, 16 },
        Rectangle { 240, 96, 16, 16 },
        Rectangle { 112, 112, 16, 16 },
        Rectangle { 128, 112, 16, 16 },
        Rectangle { 144, 112, 16, 16 },
        Rectangle { 160, 112, 16, 16 },
        Rectangle { 176, 112, 16, 16 },
        Rectangle { 192, 112, 16, 16 },
        Rectangle { 16, 48, 16, 16 },
        Rectangle { 32, 48, 16, 16 },
        Rectangle { 48, 48, 16, 16 },
        Rectangle { 48, 64, 16, 16 },
        Rectangle { 64, 64, 16, 16 },
        Rectangle { 80, 64, 16, 16 },
        Rectangle { 96, 64, 16, 16 },
        Rectangle { 64, 48, 16, 16 },
        Rectangle { 80, 48, 16, 16 },
        Rectangle { 80, 80, 16, 16 },
        Rectangle { 96, 80, 16, 16 },
        Rectangle { 96, 64, 16, 16 },
        Rectangle { 0, 16, 16, 16 },
        Rectangle { 64, 96, 16, 16 }
    };

    short map[TILEMAP_HEIGHT][TILEMAP_WIDTH] = {
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0  },
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 3, 3, 3, 11,0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
        {  4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 4, 5, 0, 0, 0, 3, 3, 11,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11,0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 11,0, 0, 0, 3, 3, 3, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 3, 11,0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 2, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
        {  0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 3, 11,3, 3, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11,0, 0, 0, 11,0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 11,2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
        {  0, 0, 0, 0, 0, 0, 0, 13,14,15,0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 11,0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 11,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11,11,0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 11,0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13,14,15,0, 0  },
        {  0, 0, 0, 0, 0, 0, 16,17,18,19,20,0, 0, 0, 0, 0, 3, 0, 45,0, 0, 0, 0, 0, 0, 45,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45,0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 11,0, 0, 0, 0, 2, 3, 3, 3, 11,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45,45,0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16,17,18,19,20,0  },
        {  0, 0, 0, 0, 0, 0, 21,23,24,25,22,0, 0, 0, 0, 0, 0, 45,53,0, 0, 0, 0, 0, 0, 53,0, 0, 0, 45,11,12,0, 0, 3, 3, 0, 45,53,0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 45,45,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45,0, 0, 0, 0, 0, 11,0, 0, 11,3, 11,0, 0, 0, 0, 0, 0, 69,3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 53,53,0, 2, 0, 45,45,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 45,57,58,59,0, 45,45,0, 0, 0, 0, 21,23,70,25,22,45 },
        {  0, 0, 0, 0, 0, 0, 21,26,27,28,22,0, 0, 0, 0, 51,52,53,53,0, 45,0, 0, 0, 0, 53,0, 34,35,53,0, 0, 0, 0, 0, 0, 0, 53,53,45,0, 0, 0, 45,0, 0, 0, 0, 0, 0, 0, 0, 0, 45,0, 51,52,0, 0, 53,53,34,35,12,3, 11,3, 0, 45,0, 45,0, 0, 0, 53,45,0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 45,45,45,45,45,45,0, 0, 0, 0, 0, 0, 0, 0, 51,52,0, 3, 0, 0, 0, 53,53,0, 3, 0, 53,53,0, 0, 12,0, 0, 0, 0, 0, 0, 0, 2, 0, 3, 53,60,61,62,64,53,53,0, 0, 0, 0, 21,26,27,28,22,53 },
        {  0, 0, 0, 0, 0, 0, 21,26,27,28,22,0, 0, 0, 0, 54,55,56,56,36,56,0, 0, 0, 0, 56,42,43,44,56,0, 0, 0, 0, 0, 0, 0, 56,56,56,0, 0, 0, 56,0, 0, 0, 0, 0, 0, 0, 36,36,56,0, 54,55,0, 0, 56,56,43,44,0, 0, 0, 0, 0, 56,36,56,36,36,0, 56,56,36,0, 0, 0, 0, 0, 0, 36,36,36,56,56,56,56,56,56,0, 36,36,0, 0, 0, 0, 0, 54,55,0, 0, 0, 0, 0, 56,56,0, 3, 0, 56,56,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 3, 56,65,66,67,63,56,56,0, 0, 0, 0, 21,26,27,28,22,56 },
        {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  },
        {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  }
    };

    short physics[TILEMAP_HEIGHT][TILEMAP_WIDTH] = {
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  },
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  },
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  },
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  },
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  },
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  },
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  },
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  },
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  },
        {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  },
        {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  },
        {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  }
    };

    Particles defaultParticles = Particles{ ResourceManager::getTexture("tiles"), { Rectangle { 112, 16, 7, 7 }, Rectangle { 120, 16, 7, 7 } } };
    std::map<int, Breakable*> breakables;
    breakables[TILE_YROCK] = new Breakable(defaultParticles);
    breakables[TILE_BOXITEM] = new BaumDrop(defaultParticles);
    breakables[TILE_BOXSTUN] = new Breakable(defaultParticles);
    breakables[TILE_BOXQST] = new Breakable(defaultParticles);

    // initialize scene
    Scene* scene = new Scene();
    scene->background = Color { 0, 0, 255, 255 };
    scene->music = ResourceManager::getMusic("main_theme");

    // initialize tile map
    TileMap* tileMap = new TileMap();
    tileMap->render->texture = atlas;
    tileMap->render->setTileSet(tiles);
    tileMap->render->setTileMap(map);
    tileMap->physics->setTileMap(physics);
    tileMap->breakables = breakables;
    scene->push(tileMap);

    // animated quicksand tiles
    scene->push(new TileAnimationController(
        tileMap,
        { TILE_QSND0, TILE_QSND1, TILE_QSND2, TILE_QSND3 },
        {
            TileCoords { 32, 10 }, TileCoords { 33, 10 }, TileCoords { 34, 10 }, TileCoords { 35, 10 },
            TileCoords { 45, 10 }, TileCoords { 46, 10 }, TileCoords { 47, 10 }, TileCoords { 48, 10 },
            TileCoords { 78, 10 }, TileCoords { 79, 10 }, TileCoords { 80, 10 }, TileCoords { 81, 10 }
        }
    ));

    // baum bags
    scene->push(new BaumPickup(Vector2 { 448.0f, 0.0f }, true));
    scene->push(new BaumPickup(Vector2 { 448.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 464.0f, 0.0f }, true));
    scene->push(new BaumPickup(Vector2 { 464.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 480.0f, 0.0f }, true));
    scene->push(new BaumPickup(Vector2 { 480.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 480.0f, 32.0f }, true));
    scene->push(new BaumPickup(Vector2 { 480.0f, 48.0f }, true));
    scene->push(new BaumPickup(Vector2 { 480.0f, 64.0f }, true));
    scene->push(new BaumPickup(Vector2 { 496.0f, 0.0f }, true));
    scene->push(new BaumPickup(Vector2 { 496.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 848.0f, 96.0f }, true));
    scene->push(new BaumPickup(Vector2 { 928.0f, 0.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1040.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1056.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1296.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1312.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1328.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1408.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1424.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1456.0f, 16.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1536.0f, 48.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1536.0f, 64.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1536.0f, 80.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1536.0f, 96.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1616.0f, 0.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1632.0f, 0.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1744.0f, 112.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1888.0f, 128.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1920.0f, 0.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1936.0f, 80.0f }, true));
    scene->push(new BaumPickup(Vector2 { 1952.0f, 48.0f }, true));

    // player
    Player* player = new Player();
	player->tileMap = tileMap;
	player->physics->aabb.position.x = 129.0f; // 10.0f;
	player->physics->aabb.position.y = 136.0f;
	scene->push(player);

    //HACER DOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOR
    Door* door = new Door(Vector2{ 129, 112 }, player);
    scene->push(door);

	// camera controller
	CameraController* cameraController = new CameraController();
	cameraController->player = player;
	cameraController->mode = CAM_RIGHT;
	cameraController->limits.x = 2048.0f;
	scene->push(cameraController);

	// scorpions
    WanderingEnemy* scorpion0 = SceneFactory::scorpion();
    scorpion0->physics->aabb.position = Vector2 { 672.0f, 99.0f };
    scorpion0->direction = -1;
    scorpion0->wander_distance = 32.0f;
    scene->push(scorpion0);

    WanderingEnemy* scorpion1 = SceneFactory::scorpion();
    scorpion1->physics->aabb.position = Vector2 { 1232.0f, 147.0f };
    scorpion1->direction = -1;
    scorpion1->wander_distance = 216.0f;
    scene->push(scorpion1);

    WanderingEnemy* scorpion2 = SceneFactory::scorpion();
    scorpion2->physics->aabb.position = Vector2 { 1000.0f, 147.0f };
    scorpion2->direction = -1;
    scorpion2->wander_distance = 216.0f;
    scene->push(scorpion2);

    WanderingEnemy* scorpion3 = SceneFactory::scorpion();
    scorpion3->physics->aabb.position = Vector2 { 1742.0f, 147.0f };
    scorpion3->direction = -1;
    scorpion3->wander_distance = 960.0f;
    scene->push(scorpion3);

	// onigiri
	scene->push(new Onigiri(Vector2 { 2244.0f, 128.0f }, true));

    // play music
    SetMusicVolume(*scene->music, 0.5f);
    PlayMusicStream(*scene->music);

    return scene;
}

Scene* SceneFactory::gameOver() {
    // initialize scene
    Scene* scene = new Scene();
    scene->background = BLACK;

    // instance screen
    scene->push(new GameOverController());

    // play music
    Sound* jingle = ResourceManager::getSound("game_over");
    SetSoundVolume(*jingle, 0.5f);
    PlaySound(*jingle);

    return scene;
}

WanderingEnemy* SceneFactory::scorpion() {
    WanderingEnemy* scorpion = new WanderingEnemy();
    scorpion->physics->aabb.size = Vector2 { 16, 13 };
    scorpion->walk_speed = 40.0f;
    scorpion->sprite->animation = new Animation();
    scorpion->sprite->animation->texture = ResourceManager::getTexture("scorpion");
    scorpion->sprite->animation->frames = {
        Rectangle { 0, 2, 16, 14 },
    	Rectangle { 16, 2, 16, 14 }
    };
    scorpion->sprite->frame_rate = 2.0f;
    return scorpion;
}

Scene* SceneFactory::shop() {
    // level data definition
    Texture2D* atlas = ResourceManager::getTexture("shop");

    enum {
        TILE_NONE,
        TILE_FLOOR,
        TILE_ARCL0,
        TILE_ARCL1,
        TILE_ARCL2,
        TILE_ARCL3,
        TILE_ARCL4,
        TILE_ARCL5,
        TILE_ARCR0,
        TILE_ARCR1,
        TILE_ARCR2,
        TILE_ARCR3,
        TILE_ARCR4,
        TILE_ARCR5,
        TILE_BEAM,
        TILE_WALL,
        TILE_CEIL,
        TILE_CRTL0,
        TILE_CRTL1,
        TILE_CRTL2,
        TILE_CRTL3,
        TILE_CRTL4,
        TILE_CRTR0,
        TILE_CRTR1,
        TILE_CRTR2,
        TILE_CRTR3,
        TILE_CRTR4,
        TILE_DOORL0,
        TILE_DOORL1,
        TILE_DOORL2,
        TILE_DOORR0,
        TILE_DOORR1,
        TILE_DOORR2,
        TILE_FRM0,
        TILE_FRM1,
        TILE_FRM2,
        TILE_FRM3,
        TILE_FRM4,
        TILE_FRM5,
        TILE_FRM6,
        TILE_FRM7,
        TILE_FRM8,
        TILE_FRM9,
        TILE_FRM10,
        TILE_KPR0,
        TILE_KPR1,
        TILE_KPR2,
        TILE_KPR3,
        TILE_KPR4,
        TILE_KPR5,
        TILE_KPR6,
        TILE_KPR7,
        TILE_HUD0,
        TILE_HUD1,
        TILE_HUD2,
        TILE_HUD3,
        TILE_HUD4,
    };

    Rectangle tiles[128] = {
        Rectangle { 0 },
        Rectangle { 0, 48, 16, 16 },
        Rectangle { 0, 32, 16, 16 },
        Rectangle { 0, 16, 16, 16 },
        Rectangle { 16, 16, 16, 16 },
        Rectangle { 16, 0, 16, 16 },
        Rectangle { 32, 0, 16, 16 },
        Rectangle { 48, 0, 16, 16 },
        Rectangle { 112, 32, 16, 16 },
        Rectangle { 112, 16, 16, 16 },
        Rectangle { 96, 16, 16, 16 },
        Rectangle { 96, 0, 16, 16 },
        Rectangle { 80, 0, 16, 16 },
        Rectangle { 64, 0, 16, 16 },
        Rectangle { 48, 16, 16, 16 },
        Rectangle { 48, 32, 16, 16 },
        Rectangle { 64, 32, 16, 16 },
        Rectangle { 16, 32, 16, 16 },
        Rectangle { 16, 48, 16, 16 },
        Rectangle { 32, 16, 16, 16 },
        Rectangle { 32, 32, 16, 16 },
        Rectangle { 32, 48, 16, 16 },
        Rectangle { 96, 32, 16, 16 },
        Rectangle { 96, 48, 16, 16 },
        Rectangle { 80, 16, 16, 16 },
        Rectangle { 80, 32, 16, 16 },
        Rectangle { 80, 48, 16, 16 },
        Rectangle { 48, 48, 16, 16 },
        Rectangle { 48, 64, 16, 16 },
        Rectangle { 48, 80, 16, 16 },
        Rectangle { 64, 48, 16, 16 },
        Rectangle { 64, 64, 16, 16 },
        Rectangle { 64, 80, 16, 16 },
        Rectangle { 80, 64, 16, 16 },
        Rectangle { 96, 64, 16, 16 },
        Rectangle { 112, 64, 16, 16 },
        Rectangle { 80, 80, 16, 16 },
        Rectangle { 112, 80, 16, 16 },
        Rectangle { 80, 96, 16, 16 },
        Rectangle { 96, 96, 16, 16 },
        Rectangle { 112, 96, 16, 16 },
        Rectangle { 80, 112, 16, 16 },
        Rectangle { 96, 112, 16, 16 },
        Rectangle { 112, 112, 16, 16 },
        Rectangle { 16, 64, 16, 16 },
        Rectangle { 32, 64, 16, 16 },
        Rectangle { 16, 80, 16, 16 },
        Rectangle { 32, 80, 16, 16 },
        Rectangle { 0, 96, 16, 16 },
        Rectangle { 16, 96, 16, 16 },
        Rectangle { 32, 96, 16, 16 },
        Rectangle { 48, 96, 16, 16 },
        Rectangle { 0, 112, 16, 16 },
        Rectangle { 16, 112, 16, 16 },
        Rectangle { 32, 112, 16, 16 },
        Rectangle { 48, 112, 16, 16 },
        Rectangle { 64, 112, 16, 16 },
    };

    short map[TILEMAP_HEIGHT][TILEMAP_WIDTH] = {
        { 0, 5, 6, 7, 16,16,16,16,16,16,16,16,13,12,11,0 },
        { 3, 4, 14,14,14,14,14,14,14,14,14,14,14,14,10,9 },
        { 2, 17,15,15,15,15,15,15,15,15,15,15,15,15,22,8 },
        { 2, 18,15,15,15,15,15,15,15,15,15,15,15,15,23,8 },
        { 2, 19,15,15,15,33,34,34,34,34,35,15,15,15,24,8 },
        { 2, 20,15,15,15,36,0, 0, 0, 0, 37,15,15,15,25,8 },
        { 2, 21,27,30,15,38,39,39,39,39,40,15,15,15,26,8 },
        { 2, 17,28,31,15,41,42,42,42,42,43,15,44,45,22,8 },
        { 2, 18,29,32,15,15,15,15,15,15,15,15,46,47,23,8 },
        { 2, 19,29,32,15,15,15,15,15,15,15,48,49,50,51,8 },
        { 1, 52,53,54,55,56,1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    };

    short physics[TILEMAP_HEIGHT][TILEMAP_WIDTH] = {
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    };

    // initialize scene
    Scene* scene = new Scene();
    scene->background = Color { 0, 0, 255, 255 };
    scene->music = ResourceManager::getMusic("main_theme");

    // initialize tile map
    TileMap* tileMap = new TileMap();
    tileMap->render->texture = atlas;
    tileMap->render->setTileSet(tiles);
    tileMap->render->setTileMap(map);
    tileMap->physics->setTileMap(physics);
    scene->push(tileMap);

    // buy pogo stick
    if (GameState::shop[0]) {
        PurchaseOption* pogoStick = new PurchaseOption();
        pogoStick->slot = 0;
        pogoStick->item = BUY_POGOSTICK;
        pogoStick->setPrice(100);
        pogoStick->sprite->texture = ResourceManager::getTexture("items");
        pogoStick->sprite->frame = Rectangle { 0, 16, 16, 16 };
        pogoStick->placeAt(Vector2 { 104, 86 });
        scene->push(pogoStick);
    }

    // buy extra life
    if (GameState::shop[1]) {
        PurchaseOption* extraLife = new PurchaseOption();
        extraLife->slot = 1;
        extraLife->item = BUY_LIFE;
        extraLife->setPrice(200);
        extraLife->sprite->texture = ResourceManager::getTexture("items");
        extraLife->sprite->frame = Rectangle { 48, 0, 16, 16 };
        extraLife->placeAt(Vector2 { 136, 86 });
        scene->push(extraLife);
    }

    // player
    Player* player = new Player();
	player->tileMap = tileMap;
	player->physics->aabb.position.x = 38.0f;
	player->physics->aabb.position.y = 136.0f;
	scene->push(player);

    // exit door
    scene->push(new Door(Vector2{ 38, 112 }, player, true));

    // coin counter
    scene->push(new CoinCounter(Vector2 { 87, 167 }));

    // play music
    SetMusicVolume(*scene->music, 0.5f);
    PlayMusicStream(*scene->music);

    return scene;
}
