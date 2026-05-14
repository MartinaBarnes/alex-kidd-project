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
#include "WanderingEnemy.h"
#include "Onigiri.h"
#include "GameState.h"
#include "GameOverController.h"
#include "MapTransitionController.h"
#include "TitleSplashController.h"
#include "IntroSplashController.h"

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
    scene->push(new MapTransitionController());

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

    Rectangle tiles[64] = {
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

    Breakable defaultBreakable = Breakable(Particles { ResourceManager::getTexture("tiles"), { Rectangle { 112, 16, 7, 7 } } });

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
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  1,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  1,  1,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  1,  1,  0,  0,  0,  1,  1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1,  0,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  1,  1,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1   },
        {   4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4   },
        {   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  3,  3,  3,  1,  1,  1,  1,  1,  1,  1,  1,  3,  3,  3,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   },
    };

    std::map<int, Breakable> breakables;
    breakables[TILE_BOXITEM] = defaultBreakable;
    breakables[TILE_BOXSTUN] = defaultBreakable;
    breakables[TILE_BORB] = Breakable(Particles { ResourceManager::getTexture("tiles"), { Rectangle { 112, 24, 8, 8 } } });

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
	player->physics->aabb.position.y = 136 + 8;
	scene->push(player);

	// camera controller
	CameraController* cameraController = new CameraController();
	cameraController->player = player;
	cameraController->mode = CAM_RIGHT;
	cameraController->limits.x = 992;
	scene->push(cameraController);

	// scorpion
	WanderingEnemy* scorpion = new WanderingEnemy();
	scorpion->physics->aabb.position = Vector2 { 62 * TILE_SIZE, 4 * TILE_SIZE + 3 };
	scorpion->physics->aabb.size = Vector2 { 16, 13 };
	scorpion->direction = -1;
	scorpion->walk_speed = 40.0f;
	scorpion->wander_distance = 6 * TILE_SIZE;
	scorpion->sprite->animation = new Animation();
	scorpion->sprite->animation->texture = ResourceManager::getTexture("scorpion");
	scorpion->sprite->animation->frames = {
	    Rectangle { 0, 3, 16, 13 },
		Rectangle { 16, 3, 16, 13 }
	};
	scorpion->sprite->frame_rate = 2.0f;
	scene->push(scorpion);

	// TODO: add second scorpion

	// onigiri
	scene->push(new Onigiri(Vector2 { 75 * TILE_SIZE, 7 * TILE_SIZE }));

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

    // first level -- reset lives
    GameState::lives = 3;

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
