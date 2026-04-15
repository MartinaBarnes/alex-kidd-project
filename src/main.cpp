#include "ResourceManager.h"
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "PhysicsTileMap.h"
#include "RenderTileMap.h"
#include "TileMap.h"
#include "Player.h"
#include "WanderingEnemy.h"
#include "Scene.h"
#include <cmath>

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Alex Kidd in Miracle World");

	ResourceManager::loadResources();

	AABB* bounds = new AABB(0, 0, 1280, 800);

	TileMap* tilemap = new TileMap();
	tilemap->physics->map[1][31] = PHYSTILE_SOLID;
	tilemap->physics->map[16][31] = PHYSTILE_SOLID;
	tilemap->physics->map[16][30] = PHYSTILE_SOLID;
	tilemap->physics->map[24][31] = PHYSTILE_SOLID;
	for (int i = 0; i < 128; i++) {
		tilemap->physics->map[i][32] = PHYSTILE_SOLID;
	}
	tilemap->render->texture = ResourceManager::getTexture("tiles");
	tilemap->render->tiles[0] = Rectangle { 48, 0, 16, 16 };
	tilemap->render->tiles[1] = Rectangle { 48, 32, 16, 16 };
	tilemap->render->map[1][31] = 1;
	tilemap->render->map[16][31] = 2;
	tilemap->render->map[16][30] = 1;
	tilemap->render->map[24][31] = 1;
	for (int i = 0; i < 128; i++) {
		tilemap->render->map[i][32] = 1;
		if (i == 1 || i == 16 || i == 24) {
		    tilemap->render->map[i][32] = 2;
		}
		tilemap->render->map[i][33] = 2;
	}
	tilemap->render->bounds = bounds;

	Player* player = new Player();
	WanderingEnemy* enemy = new WanderingEnemy();
	enemy->walk_speed = 100.0f;
	enemy->physics->aabb.size = { 16, 16 };
	enemy->physics->aabb.position.x = 16 * TILE_SIZE;
	enemy->physics->aabb.position.y = 31 * TILE_SIZE;
	enemy->sprite->animation = new Animation();
	enemy->sprite->animation->texture = ResourceManager::getTexture("wabbit_alpha");
	enemy->sprite->animation->frames.push_back(Rectangle { 0, 0, 32, 32 });

	Scene* scene = new Scene();
	scene->push(tilemap);
	scene->push(player);
	scene->push(enemy);

	// game loop
	while (!WindowShouldClose()) // run the loop until the user presses ESCAPE or presses the Close button on the window
	{
	    float dt = GetFrameTime();
        scene->update(dt);
		PhysicsServer::update(dt, bounds);

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLUE);

		RenderingServer::update(dt, bounds);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	ResourceManager::unloadResources();

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
