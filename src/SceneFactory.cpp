#include "SceneFactory.h"
#include "PhysicsTileMap.h"
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
    // first level -- reset lives
    GameState::lives = 3;

    // initialize scene
    Scene* scene = new Scene();
    scene->background = Color { 0, 0, 255, 255 };
    scene->music = ResourceManager::getMusic("main_theme");

    enum {
        TILE_NONE,
        TILE_GRASS,
        TILE_TALLGRASS,
        TILE_BLUEORB,
        TILE_REDORB,
        TILE_TREETOP0,
        TILE_TREETOP1,
        TILE_TREETRUNK,
        TILE_CLOUD0,
        TILE_CLOUD1,
        TILE_LAVASTILL,
        TILE_LAVA0,
        TILE_LAVA1,
        TILE_LAVA2,
        TILE_LAVA3,
        TILE_BOXITEM,
        TILE_BOXSTUN,
        TILE_TEMPLETOP0L,
        TILE_TEMPLETOP0R,
        TILE_TEMPLETOP1L,
        TILE_TEMPLETOP1R,
        TILE_TEMPLESIDE0L,
        TILE_TEMPLESIDE1L,
        TILE_TEMPLESIDE0R,
        TILE_TEMPLESIDE1R,
        TILE_TEMPLECENTER0,
        TILE_TEMPLECENTER1,
        TILE_TEMPLECENTER2,
        TILE_TEMPLECENTER3,
        TILE_TEMPLECENTER4,
        TILE_TEMPLECENTER5,
        TILE_TEMPLECENTER6,
        TILE_TEMPLECENTER7,
        TILE_TEMPLECENTER8,
        TILE_TEMPLEGRASS,
    };

    Texture2D* tiles = ResourceManager::getTexture("tiles");

    TileMap* tileMap = new TileMap();
    scene->push(tileMap);

    // tile set
    tileMap->render->texture = tiles;
    tileMap->render->tiles[TILE_GRASS] = Rectangle { 0, 48, 16, 16 };
    tileMap->render->tiles[TILE_TALLGRASS] = Rectangle { 0, 32, 16, 16 };
    tileMap->render->tiles[TILE_BLUEORB] = Rectangle { 96, 32, 16, 16 };
    tileMap->render->tiles[TILE_REDORB] = Rectangle { 80, 0, 16, 16 };
    tileMap->render->tiles[TILE_TREETOP0] = Rectangle { 176, 0, 16, 16 };
    tileMap->render->tiles[TILE_TREETOP1] = Rectangle { 176, 16, 16, 16 };
    tileMap->render->tiles[TILE_TREETRUNK] = Rectangle { 176, 32, 16, 16 };
    tileMap->render->tiles[TILE_CLOUD0] = Rectangle { 112, 0, 16, 16 };
    tileMap->render->tiles[TILE_CLOUD1] = Rectangle { 128, 0, 16, 16 };
    tileMap->render->tiles[TILE_LAVASTILL] = Rectangle { 112, 48, 16, 16 };
    tileMap->render->tiles[TILE_LAVA0] = Rectangle { 128, 32, 16, 16 };
    tileMap->render->tiles[TILE_LAVA1] = Rectangle { 144, 32, 16, 16 };
    tileMap->render->tiles[TILE_LAVA2] = Rectangle { 160, 32, 16, 16 };
    tileMap->render->tiles[TILE_LAVA3] = Rectangle { 112, 32, 16, 16 };
    tileMap->render->tiles[TILE_BOXITEM] = Rectangle { 16, 0, 16, 16 };
    tileMap->render->tiles[TILE_BOXSTUN] = Rectangle { 16, 16, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLETOP0L] = Rectangle { 192, 0, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLETOP1L] = Rectangle { 192, 16, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLETOP0R] = Rectangle { 208, 0, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLETOP1R] = Rectangle { 208, 16, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLESIDE0L] = Rectangle { 192, 32, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLESIDE1L] = Rectangle { 192, 48, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLESIDE0R] = Rectangle { 208, 32, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLESIDE1R] = Rectangle { 208, 48, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLECENTER0] = Rectangle { 224, 0, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLECENTER1] = Rectangle { 240, 0, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLECENTER2] = Rectangle { 224, 16, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLECENTER3] = Rectangle { 240, 16, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLECENTER4] = Rectangle { 224, 32, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLECENTER5] = Rectangle { 240, 32, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLECENTER6] = Rectangle { 224, 48, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLECENTER7] = Rectangle { 240, 48, 16, 16 };
    tileMap->render->tiles[TILE_TEMPLEGRASS] = Rectangle { 16, 32, 16, 16 };

    // blue orb particles
    Rectangle blueParticles = Rectangle { 112, 24, 8, 8 };

    // tile map
    tileMap->render->map[0][1] = TILE_CLOUD0;
    tileMap->render->map[1][1] = TILE_CLOUD1;

    tileMap->render->map[0][4] = TILE_TREETOP0;
    tileMap->render->map[0][5] = TILE_TREETOP1;
    tileMap->render->map[0][6] = TILE_TREETOP1;
    tileMap->render->map[0][7] = TILE_TREETOP1;
    tileMap->render->map[0][8] = TILE_TREETRUNK;
    tileMap->render->map[0][9] = TILE_TREETRUNK;

    tileMap->render->map[1][5] = TILE_TREETOP0;
    tileMap->render->map[1][6] = TILE_TREETOP1;
    tileMap->render->map[1][7] = TILE_TREETOP1;
    tileMap->render->map[1][8] = TILE_TREETRUNK;
    tileMap->render->map[1][9] = TILE_TREETRUNK;

    tileMap->render->map[8][5] = TILE_TREETOP0;
    tileMap->render->map[8][6] = TILE_TREETOP1;
    tileMap->render->map[8][7] = TILE_TREETOP1;
    tileMap->render->map[8][8] = TILE_TREETRUNK;
    tileMap->render->map[8][9] = TILE_TREETRUNK;

    tileMap->render->map[11][2] = TILE_CLOUD0;
    tileMap->render->map[12][2] = TILE_CLOUD1;

    tileMap->render->map[13][6] = TILE_TREETOP0;
    tileMap->render->map[13][7] = TILE_TREETOP1;
    tileMap->render->map[13][8] = TILE_TREETOP1;
    tileMap->render->map[13][9] = TILE_TREETRUNK;

    tileMap->render->map[16][0] = TILE_CLOUD0;
    tileMap->render->map[17][0] = TILE_CLOUD1;

    tileMap->render->map[20][1] = TILE_CLOUD0;
    tileMap->render->map[21][1] = TILE_CLOUD1;

    tileMap->render->map[24][2] = TILE_CLOUD0;
    tileMap->render->map[25][2] = TILE_CLOUD1;

    tileMap->render->map[29][7] = TILE_TREETOP0;
    tileMap->render->map[29][8] = TILE_TREETOP1;
    tileMap->render->map[29][9] = TILE_TREETRUNK;

    tileMap->render->map[29][0] = TILE_CLOUD0;
    tileMap->render->map[30][0] = TILE_CLOUD1;

    tileMap->render->map[30][5] = TILE_TREETOP0;
    tileMap->render->map[30][6] = TILE_TREETOP1;
    tileMap->render->map[30][7] = TILE_TREETOP1;
    tileMap->render->map[30][8] = TILE_TREETRUNK;
    tileMap->render->map[30][9] = TILE_TREETRUNK;

    tileMap->render->map[33][3] = TILE_TREETOP0;
    tileMap->render->map[33][4] = TILE_TREETOP1;
    tileMap->render->map[33][5] = TILE_TREETOP1;
    tileMap->render->map[33][6] = TILE_TREETOP1;
    tileMap->render->map[33][7] = TILE_TREETRUNK;
    tileMap->render->map[33][8] = TILE_TREETRUNK;
    tileMap->render->map[33][9] = TILE_TREETRUNK;

    tileMap->render->map[39][2] = TILE_CLOUD0;
    tileMap->render->map[40][2] = TILE_CLOUD1;

    tileMap->render->map[43][4] = TILE_TREETOP0;
    tileMap->render->map[43][5] = TILE_TREETOP1;
    tileMap->render->map[43][6] = TILE_TREETOP1;
    tileMap->render->map[43][7] = TILE_TREETOP1;
    tileMap->render->map[43][8] = TILE_TREETRUNK;
    tileMap->render->map[43][9] = TILE_TREETRUNK;

    tileMap->render->map[44][0] = TILE_CLOUD0;
    tileMap->render->map[45][0] = TILE_CLOUD1;

    tileMap->render->map[46][3] = TILE_TREETOP0;
    tileMap->render->map[46][4] = TILE_TREETOP1;
    tileMap->render->map[46][5] = TILE_TREETOP1;
    tileMap->render->map[46][6] = TILE_TREETOP1;
    tileMap->render->map[46][7] = TILE_TREETRUNK;
    tileMap->render->map[46][8] = TILE_TREETRUNK;
    tileMap->render->map[46][9] = TILE_TREETRUNK;

    tileMap->render->map[49][5] = TILE_TREETOP0;
    tileMap->render->map[49][6] = TILE_TREETOP1;
    tileMap->render->map[49][7] = TILE_TREETOP1;
    tileMap->render->map[49][8] = TILE_TREETRUNK;
    tileMap->render->map[49][9] = TILE_TREETRUNK;

    tileMap->render->map[50][2] = TILE_CLOUD0;
    tileMap->render->map[51][2] = TILE_CLOUD1;

    tileMap->render->map[58][1] = TILE_CLOUD0;
    tileMap->render->map[59][1] = TILE_CLOUD1;

    tileMap->render->map[63][3] = TILE_CLOUD0;
    tileMap->render->map[64][3] = TILE_CLOUD1;

    tileMap->render->map[63][5] = TILE_TREETOP0;
    tileMap->render->map[63][6] = TILE_TREETOP1;
    tileMap->render->map[63][7] = TILE_TREETOP1;
    tileMap->render->map[63][8] = TILE_TREETRUNK;
    tileMap->render->map[63][9] = TILE_TREETRUNK;

    tileMap->render->map[64][6] = TILE_TREETOP0;
    tileMap->render->map[64][7] = TILE_TREETOP1;
    tileMap->render->map[64][8] = TILE_TREETOP1;
    tileMap->render->map[64][9] = TILE_TREETRUNK;

    tileMap->render->map[65][5] = TILE_TREETOP0;
    tileMap->render->map[65][6] = TILE_TREETOP1;
    tileMap->render->map[65][7] = TILE_TREETOP1;
    tileMap->render->map[65][8] = TILE_TREETRUNK;
    tileMap->render->map[65][9] = TILE_TREETRUNK;

    tileMap->render->map[68][1] = TILE_CLOUD0;
    tileMap->render->map[69][1] = TILE_CLOUD1;

    tileMap->render->map[73][2] = TILE_CLOUD0;
    tileMap->render->map[74][2] = TILE_CLOUD1;

    tileMap->render->map[76][0] = TILE_CLOUD0;
    tileMap->render->map[77][0] = TILE_CLOUD1;

    tileMap->render->map[76][3] = TILE_TREETOP0;
    tileMap->render->map[76][4] = TILE_TREETOP1;
    tileMap->render->map[76][5] = TILE_TREETOP1;
    tileMap->render->map[76][6] = TILE_TREETOP1;
    tileMap->render->map[76][7] = TILE_TREETRUNK;
    tileMap->render->map[76][8] = TILE_TREETRUNK;
    tileMap->render->map[76][9] = TILE_TREETRUNK;

    tileMap->render->map[77][6] = TILE_TREETOP0;
    tileMap->render->map[77][7] = TILE_TREETOP1;
    tileMap->render->map[77][8] = TILE_TREETOP1;
    tileMap->render->map[77][9] = TILE_TREETRUNK;

    for (int i = 0; i < 78; i++) {
        tileMap->setTilePair(i, 10, PHYSTILE_SOLID, TILE_TALLGRASS);
        tileMap->setTilePair(i, 11, PHYSTILE_SOLID, TILE_GRASS);
    }
    for (int i = 0; i < 12; i++) {
        tileMap->physics->map[78][i] = PHYSTILE_SOLID;
    }

    std::vector<Vector2> lavaTiles;
    for (int i = 0; i < 4; i++) {
        int x0 = 24 + i;
        int x1 = 36 + i;

        tileMap->setTilePair(x0, 11, PHYSTILE_DEATHPIT, TILE_LAVASTILL);
        tileMap->setTilePair(x1, 11, PHYSTILE_DEATHPIT, TILE_LAVASTILL);

        tileMap->physics->map[x0][10] = PHYSTILE_AIR;
        tileMap->physics->map[x1][10] = PHYSTILE_AIR;
        lavaTiles.push_back(Vector2 { (float)x0, 10 });
        lavaTiles.push_back(Vector2 { (float)x1, 10 });
    }
    scene->push(new TileAnimationController(tileMap, { TILE_LAVA0, TILE_LAVA1, TILE_LAVA2, TILE_LAVA3 }, lavaTiles));

    tileMap->setTilePair(4, 2, PHYSTILE_SOLID, TILE_BOXITEM);
    scene->push(new Breakable(tileMap, Vector2 { 4, 2 }));

    tileMap->setTilePair(8, 1, PHYSTILE_SOLID, TILE_BOXITEM);
    scene->push(new Breakable(tileMap, Vector2 { 8, 1 }));

    for (float x = 2; x <= 3; x++) {
        for (float y = 8; y <= 9; y++) {
            tileMap->setTilePair(x, y, PHYSTILE_SOLID, TILE_BLUEORB);
            scene->push(new Breakable(tileMap, Vector2 { x, y }, tiles, blueParticles));
        }
    }

    for (float x = 6; x <= 7; x++) {
        for (float y = 7; y <= 9; y++) {
            if (x == 7 && y == 8) {
                tileMap->setTilePair(x, y, PHYSTILE_SOLID, TILE_BOXSTUN);
                scene->push(new Breakable(tileMap, Vector2 { x, y }));
                continue;
            }
            tileMap->setTilePair(x, y, PHYSTILE_SOLID, TILE_BLUEORB);
            scene->push(new Breakable(tileMap, Vector2 { x, y }, tiles, blueParticles));
        }
    }

    for (float x = 10; x <= 11; x++) {
        for (float y = 6; y <= 9; y++) {
            if (x == 11 && y >= 8) {
                break;
            }
            tileMap->setTilePair(x, y, PHYSTILE_SOLID, TILE_BLUEORB);
            if (x == 10 && y == 8) {
                scene->push(new Breakable(tileMap, Vector2 { x, y }));
                continue;
            }
            scene->push(new Breakable(tileMap, Vector2 { x, y }, tiles, blueParticles));
        }
    }
    tileMap->render->map[10][8] = TILE_BOXSTUN;
    tileMap->setTilePair(10, 3, PHYSTILE_SOLID, TILE_REDORB);
    tileMap->setTilePair(11, 8, PHYSTILE_SOLID, TILE_REDORB);
    tileMap->setTilePair(11, 9, PHYSTILE_SOLID, TILE_REDORB);

    for (float y = 5; y <= 8; y++) {
        tileMap->setTilePair(14, y, PHYSTILE_SOLID, TILE_BLUEORB);
        scene->push(new Breakable(tileMap, Vector2 { 14, y }, tiles, blueParticles));
    }
    tileMap->setTilePair(14, 9, PHYSTILE_SOLID, TILE_REDORB);
    tileMap->setTilePair(15, 5, PHYSTILE_SOLID, TILE_BOXITEM);
    scene->push(new Breakable(tileMap, Vector2 { 15, 5 }));
    tileMap->setTilePair(15, 6, PHYSTILE_SOLID, TILE_BOXITEM);
    scene->push(new Breakable(tileMap, Vector2 { 15, 6 }));
    tileMap->setTilePair(15, 7, PHYSTILE_SOLID, TILE_REDORB);
    tileMap->setTilePair(15, 8, PHYSTILE_SOLID, TILE_BOXSTUN);
    scene->push(new Breakable(tileMap, Vector2 { 15, 8 }));
    tileMap->setTilePair(15, 9, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 15, 9 }, tiles, blueParticles));

    tileMap->setTilePair(17, 3, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 17, 3 }, tiles, blueParticles));

    tileMap->setTilePair(17, 8, PHYSTILE_SOLID, TILE_BOXSTUN);
    scene->push(new Breakable(tileMap, Vector2 { 17, 8 }));

    for (float y = 6; y <= 9; y++) {
        if (y == 8) {
            tileMap->setTilePair(19, y, PHYSTILE_SOLID, TILE_REDORB);
            continue;
        }
        tileMap->setTilePair(19, y, PHYSTILE_SOLID, TILE_BLUEORB);
        scene->push(new Breakable(tileMap, Vector2 { 19, y }, tiles, blueParticles));
    }

    for (float x = 21; x <= 22; x++) {
        for (float y = 2; y <= 6; y++) {
            if (x == 21 && y == 5) {
                tileMap->setTilePair(x, y, PHYSTILE_SOLID, TILE_REDORB);
                continue;
            }
            tileMap->setTilePair(x, y, PHYSTILE_SOLID, TILE_BLUEORB);
            if (y == 4) {
                scene->push(new Breakable(tileMap, Vector2 { x, y }));
                continue;
            }
            scene->push(new Breakable(tileMap, Vector2 { x, y }, tiles, blueParticles));
        }
    }
    tileMap->render->map[21][4] = TILE_BOXSTUN;
    tileMap->render->map[22][4] = TILE_BOXITEM;

    tileMap->setTilePair(24, 7, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 24, 7 }, tiles, blueParticles));

    tileMap->setTilePair(26, 3, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 26, 3 }, tiles, blueParticles));

    tileMap->setTilePair(29, 6, PHYSTILE_SOLID, TILE_REDORB);
    tileMap->setTilePair(30, 2, PHYSTILE_SOLID, TILE_REDORB);

    tileMap->setTilePair(32, 8, PHYSTILE_SOLID, TILE_REDORB);
    tileMap->setTilePair(32, 7, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 32, 7 }, tiles, blueParticles));
    tileMap->setTilePair(32, 2, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 32, 2 }, tiles, blueParticles));

    for (float x = 34; x <= 35; x++) {
        for (float y = 2; y <= 9; y++) {
            if ((x == 34 && y == 5) || (x == 35 && y == 8)) {
                tileMap->setTilePair(x, y, PHYSTILE_SOLID, TILE_REDORB);
                continue;
            }
            tileMap->setTilePair(x, y, PHYSTILE_SOLID, TILE_BLUEORB);
            if ((x == 34 && y == 3) || (x == 35 && y == 7)) {
                scene->push(new Breakable(tileMap, Vector2 { x, y }));
                continue;
            }
            scene->push(new Breakable(tileMap, Vector2 { x, y }, tiles, blueParticles));
        }
    }
    tileMap->render->map[34][3] = TILE_BOXITEM;
    tileMap->render->map[35][7] = TILE_BOXSTUN;

    tileMap->setTilePair(37, 7, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 37, 7 }, tiles, blueParticles));

    for (float x = 39; x <= 40; x++) {
        for (float y = 5; y <= 7; y++) {
            if (x == 40 && (y != 7)) {
                tileMap->setTilePair(x, y, PHYSTILE_SOLID, TILE_BOXITEM);
                scene->push(new Breakable(tileMap, Vector2 { x, y }));
                continue;
            }
            tileMap->setTilePair(x, y, PHYSTILE_SOLID, TILE_BLUEORB);
            scene->push(new Breakable(tileMap, Vector2 { x, y }, tiles, blueParticles));
        }
    }

    tileMap->setTilePair(42, 4, PHYSTILE_SOLID, TILE_REDORB);
    tileMap->setTilePair(42, 5, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 42, 5 }, tiles, blueParticles));

    tileMap->setTilePair(45, 5, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 45, 4 }, tiles, blueParticles));
    tileMap->setTilePair(45, 6, PHYSTILE_SOLID, TILE_REDORB);

    tileMap->setTilePair(48, 5, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 47, 4 }, tiles, blueParticles));

    tileMap->setTilePair(50, 6, PHYSTILE_SOLID, TILE_REDORB);

    tileMap->setTilePair(54, 2, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 54, 2 }, tiles, blueParticles));

    for (float x = 56; x <= 62; x++) {
        tileMap->setTilePair(x, 5, PHYSTILE_SOLID, TILE_REDORB);
        tileMap->setTilePair(x, 6, PHYSTILE_SOLID, TILE_BLUEORB);
        scene->push(new Breakable(tileMap, Vector2 { x, 6 }, tiles, blueParticles));
    }

    for (float x = 53; x <= 55; x++) {
        for (float y = 7; y <= 9; y++) {
            if ((y == 7 && (x == 53 || x == 54)) || (y == 8 && x == 53)) {
                continue;
            }
            tileMap->setTilePair(x, y, PHYSTILE_SOLID, TILE_BLUEORB);
            scene->push(new Breakable(tileMap, Vector2 { x, y }, tiles, blueParticles));
        }
    }
    for (float y = 7; y <= 8; y++) {
        tileMap->setTilePair(56, y, PHYSTILE_SOLID, TILE_BLUEORB);
        scene->push(new Breakable(tileMap, Vector2 { 56, y }, tiles, blueParticles));
    }
    tileMap->setTilePair(56, 9, PHYSTILE_SOLID, TILE_REDORB);
    tileMap->setTilePair(62, 7, PHYSTILE_SOLID, TILE_BLUEORB);
    scene->push(new Breakable(tileMap, Vector2 { 62, 7 }, tiles, blueParticles));
    tileMap->setTilePair(62, 8, PHYSTILE_SOLID, TILE_REDORB);
    tileMap->setTilePair(62, 9, PHYSTILE_SOLID, TILE_REDORB);

    for (float x = 58; x <= 60; x++) {
        tileMap->setTilePair(x, 8, PHYSTILE_SOLID, TILE_BOXITEM);
        scene->push(new Breakable(tileMap, Vector2 { x, 8 }));
    }

    tileMap->render->map[72][4] = TILE_TEMPLETOP0L;
    tileMap->render->map[72][5] = TILE_TEMPLETOP1L;
    tileMap->render->map[73][4] = TILE_TEMPLETOP0R;
    tileMap->render->map[73][5] = TILE_TEMPLETOP1R;
    tileMap->render->map[71][6] = TILE_TEMPLESIDE0L;
    tileMap->render->map[74][6] = TILE_TEMPLESIDE0R;
    for (int y = 7; y <= 9; y++) {
        tileMap->render->map[71][y] = TILE_TEMPLESIDE1L;
        tileMap->render->map[74][y] = TILE_TEMPLESIDE1R;
    }
    tileMap->render->map[72][6] = TILE_TEMPLECENTER0;
    tileMap->render->map[73][6] = TILE_TEMPLECENTER1;
    tileMap->render->map[72][7] = TILE_TEMPLECENTER2;
    tileMap->render->map[73][7] = TILE_TEMPLECENTER3;
    tileMap->render->map[72][8] = TILE_TEMPLECENTER4;
    tileMap->render->map[73][8] = TILE_TEMPLECENTER5;
    tileMap->render->map[72][9] = TILE_TEMPLECENTER6;
    tileMap->render->map[73][9] = TILE_TEMPLECENTER7;
    for (int x = 71; x <= 74; x++) {
        tileMap->render->map[x][10] = TILE_TEMPLEGRASS;
    }

    // player
    Player* player = new Player();
	player->tileMap = tileMap;
	player->physics->aabb.position.y = 136;
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

	// onigiri
	scene->push(new Onigiri(Vector2 { 75 * TILE_SIZE, 7 * TILE_SIZE }));

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
