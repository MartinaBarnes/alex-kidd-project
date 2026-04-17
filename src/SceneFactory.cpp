#include "SceneFactory.h"
#include "PhysicsTileMap.h"
#include "ResourceManager.h"
#include "TileAnimationController.h"
#include "TileMap.h"
#include "Player.h"
#include "CameraController.h"

Scene* SceneFactory::level1() {
    enum {
        TILE_NONE,
        TILE_GRASS,
        TILE_TALLGRASS,
        TILE_BLUEORB,
        TILE_REDORB,
        TILE_CLOUD0,
        TILE_CLOUD1,
        TILE_LAVASTILL,
        TILE_LAVA0,
        TILE_LAVA1,
        TILE_LAVA2,
        TILE_LAVA3,
        TILE_BOXITEM,
        TILE_BOXSTUN
    };

    TileMap* tileMap = new TileMap();

    // tile set
    tileMap->render->texture = ResourceManager::getTexture("tiles");
    tileMap->render->tiles[TILE_GRASS] = Rectangle { 48, 96, 16, 16 };
    tileMap->render->tiles[TILE_TALLGRASS] = Rectangle { 48, 96, 16, 16 };
    tileMap->render->tiles[TILE_BLUEORB] = Rectangle { 96, 32, 16, 16 };
    tileMap->render->tiles[TILE_REDORB] = Rectangle { 80, 0, 16, 16 };
    tileMap->render->tiles[TILE_CLOUD0] = Rectangle { 112, 0, 16, 16 };
    tileMap->render->tiles[TILE_CLOUD1] = Rectangle { 128, 0, 16, 16 };
    tileMap->render->tiles[TILE_LAVASTILL] = Rectangle { 144, 16, 16, 16 };
    tileMap->render->tiles[TILE_LAVA0] = Rectangle { 160, 0, 16, 16 };
    tileMap->render->tiles[TILE_LAVA1] = Rectangle { 176, 0, 16, 16 };
    tileMap->render->tiles[TILE_LAVA2] = Rectangle { 192, 0, 16, 16 };
    tileMap->render->tiles[TILE_LAVA3] = Rectangle { 144, 0, 16, 16 };
    tileMap->render->tiles[TILE_BOXITEM] = Rectangle { 16, 0, 16, 16 };
    tileMap->render->tiles[TILE_BOXSTUN] = Rectangle { 16, 16, 16, 16 };

    // tile map
    std::vector<Vector2> lavaTiles;
    for (int i = 0; i < 80; i++) {
        tileMap->render->map[i][10] = TILE_TALLGRASS;
        tileMap->render->map[i][11] = TILE_GRASS;

        tileMap->physics->map[i][10] = PHYSTILE_SOLID;
        tileMap->physics->map[i][11] = PHYSTILE_SOLID;
    }
    for (int i = 0; i < 12; i++) {
        tileMap->physics->map[80][i] = PHYSTILE_SOLID;
    }
    for (int i = 0; i < 4; i++) {
        int x0 = 25 + i;
        int x1 = 33 + i;

        tileMap->render->map[x0][11] = TILE_LAVASTILL;
        tileMap->render->map[x1][11] = TILE_LAVASTILL;
        lavaTiles.push_back(Vector2 { x0, 10 });
        lavaTiles.push_back(Vector2 { x1, 10 });

        tileMap->physics->map[x0][10] = PHYSTILE_AIR;
        tileMap->physics->map[x0][11] = PHYSTILE_DEATHPIT;

        tileMap->physics->map[x1][10] = PHYSTILE_AIR;
        tileMap->physics->map[x1][11] = PHYSTILE_DEATHPIT;
    }
    TileAnimationController* tileAnims = new TileAnimationController(tileMap, { TILE_LAVA0, TILE_LAVA1, TILE_LAVA2, TILE_LAVA3 }, lavaTiles);

    // player
    Player* player = new Player();
	player->tileMap = tileMap;
	player->physics->aabb.position.y = 136;

	// camera controller
	CameraController* cameraController = new CameraController();
	cameraController->player = player;
	cameraController->mode = CAM_RIGHT;
	cameraController->limits.x = 1024;

    // initialize scene
    Scene* scene = new Scene();
    scene->background = Color { 0, 0, 255, 255 };
    scene->music = ResourceManager::getMusic("main_theme");
    scene->push(tileMap);
    scene->push(tileAnims);
    scene->push(player);
    scene->push(cameraController);

    // play music
    SetMusicVolume(*scene->music, 0.5f);
    PlayMusicStream(*scene->music);

    return scene;
}
