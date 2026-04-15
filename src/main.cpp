#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "ResourceManager.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "CameraController.h"
#include "Scene.h"
#include "PhysicsTileMap.h"
#include "RenderTileMap.h"
#include "TileMap.h"
#include "Player.h"
#include "WanderingEnemy.h"
#include <cmath>

int main ()
{
    short GAME_WIDTH = 256;
    short GAME_HEIGHT = 192;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
	InitWindow(GAME_WIDTH, GAME_HEIGHT, "Alex Kidd in Miracle World");
	SetTargetFPS(60);

	RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
	Rectangle targetSrc = Rectangle { 0, 0, GAME_WIDTH, -GAME_HEIGHT };
	Rectangle targetDest = Rectangle { 0 };

	AABB* bounds = new AABB(0, 0, GAME_WIDTH + 32, GAME_HEIGHT + 32);

	ResourceManager::loadResources();

	TileMap* tilemap = new TileMap();
	tilemap->physics->map[1][9] = PHYSTILE_SOLID;
	tilemap->physics->map[5][9] = PHYSTILE_SOLID;
	tilemap->physics->map[5][8] = PHYSTILE_SOLID;
	tilemap->physics->map[12][9] = PHYSTILE_SOLID;
	for (int i = 0; i < 32; i++) {
		tilemap->physics->map[i][10] = PHYSTILE_SOLID;
	}
	tilemap->render->texture = ResourceManager::getTexture("tiles");
	tilemap->render->tiles[0] = Rectangle { 48, 0, 16, 16 };
	tilemap->render->tiles[1] = Rectangle { 48, 32, 16, 16 };
	tilemap->render->map[1][9] = 1;
	tilemap->render->map[5][9] = 2;
	tilemap->render->map[5][8] = 1;
	tilemap->render->map[12][9] = 1;
	for (int i = 0; i < 32; i++) {
		tilemap->render->map[i][10] = 1;
		if (i == 1 || i == 5 || i == 12) {
		    tilemap->render->map[i][10] = 2;
		}
		tilemap->render->map[i][11] = 2;
	}
	tilemap->render->bounds = bounds;

	Player* player = new Player();
	WanderingEnemy* enemy = new WanderingEnemy();
	enemy->walk_speed = 100.0f;
	enemy->physics->aabb.size = { 16, 16 };
	enemy->physics->aabb.position.x = 6 * TILE_SIZE;
	enemy->physics->aabb.position.y = 9 * TILE_SIZE;
	enemy->sprite->animation = new Animation();
	enemy->sprite->animation->texture = ResourceManager::getTexture("wabbit_alpha");
	enemy->sprite->animation->frames.push_back(Rectangle { 0, 0, 32, 32 });

	CameraController* cameraController = new CameraController();
	cameraController->player = player;
	cameraController->mode = CAM_RIGHT;

	Scene* scene = new Scene();
	scene->push(tilemap);
	scene->push(player);
	scene->push(enemy);
	scene->push(cameraController);

	while (!WindowShouldClose()) // run the loop until the user presses ESCAPE or presses the Close button on the window
	{
	    // automatic resolution scaling
	    short scnW = GetScreenWidth();
		short scnH = GetScreenHeight();
	    short resScale = (scnW < scnH) ? scnW / GAME_WIDTH : scnH / GAME_HEIGHT;
		targetDest.width = GAME_WIDTH * resScale;
		targetDest.height = GAME_HEIGHT * resScale;
		targetDest.x = scnW / 2 - targetDest.width / 2;
		targetDest.y = scnH / 2 - targetDest.height / 2;

		// alt + enter toggles fullscreen
		if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
		    ToggleFullscreen();
		}

		// run logic
	    float dt = GetFrameTime();
        scene->update(dt);
        bounds->position.x = RenderingServer::camera.target.x - 16;
        bounds->position.y = RenderingServer::camera.target.y - 16;

        // run physics
		PhysicsServer::update(dt, bounds);

		// draw game onto render target
		BeginTextureMode(target);
		ClearBackground(scene->background);
		RenderingServer::update(dt, bounds);
		EndTextureMode();

		// draw render target
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetSrc, targetDest, Vector2 { 0, 0 }, 0.0f, WHITE);
		EndDrawing();
	}

	ResourceManager::unloadResources();

	CloseWindow();
	return 0;
}
