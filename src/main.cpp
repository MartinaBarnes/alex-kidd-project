#include "PhysicsArea.h"
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "ResourceManager.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "CameraController.h"
#include "Breakable.h"
#include "Scene.h"
#include "SceneManager.h"
#include "PhysicsTileMap.h"
#include "RenderTileMap.h"
#include "TileMap.h"
#include "Player.h"
#include "WanderingEnemy.h"
#include "ParticleEmitter.h"
#include "TileAnimationController.h"
#include <cmath>

int main ()
{
    float GAME_WIDTH = 256.0f;
    float GAME_HEIGHT = 192.0f;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
	InitWindow(GAME_WIDTH, GAME_HEIGHT, "Alex Kidd in Miracle World");
	SetTargetFPS(60);

	RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
	Rectangle targetSrc = Rectangle { 0, 0, GAME_WIDTH, -GAME_HEIGHT };
	Rectangle targetDest = Rectangle { 0 };
	Vector2 targetPos = Vector2 { 0 };

	AABB* bounds = new AABB(0, 0, GAME_WIDTH + 32, GAME_HEIGHT + 32);

	ResourceManager::loadResources();

	TileMap* tileMap = new TileMap();
	tileMap->physics->map[1][9] = PHYSTILE_SOLID;
	tileMap->physics->map[5][9] = PHYSTILE_SOLID;
	tileMap->physics->map[5][8] = PHYSTILE_SOLID;
	tileMap->physics->map[12][9] = PHYSTILE_SOLID;
	tileMap->physics->map[24][9] = PHYSTILE_SOLID;
	for (int i = 0; i <= 24; i++) {
		tileMap->physics->map[i][10] = PHYSTILE_SOLID;
	}
	tileMap->render->texture = ResourceManager::getTexture("tiles");
	tileMap->render->tiles[0] = Rectangle { 48, 0, 16, 16 };
	tileMap->render->tiles[1] = Rectangle { 48, 32, 16, 16 };
	tileMap->render->tiles[2] = Rectangle{ 0, 16, 16, 16 };
	tileMap->render->tiles[3] = Rectangle{ 144, 16, 16, 16 };
	tileMap->render->tiles[4] = Rectangle{ 160, 0, 16, 16 };
	tileMap->render->tiles[5] = Rectangle{ 176, 0, 16, 16 };
	tileMap->render->tiles[6] = Rectangle{ 192, 0, 16, 16 };
	tileMap->render->tiles[7] = Rectangle{ 144, 0, 16, 16 };
	tileMap->render->map[1][9] = 1;
	tileMap->render->map[5][9] = 2;
	tileMap->render->map[5][8] = 1;
	tileMap->render->map[12][9] = 1;
	tileMap->render->map[24][9] = 3;
	for (int i = 0; i < 32; i++) {
	    if (i > 24) {
			tileMap->render->map[i][11] = 4;
			continue;
		}
		tileMap->render->map[i][10] = 1;
		if (i == 1 || i == 5 || i == 12) {
		    tileMap->render->map[i][10] = 2;
		}
		tileMap->render->map[i][11] = 2;
	}
	tileMap->render->bounds = bounds;

	Player* player = new Player();
	WanderingEnemy* enemy = new WanderingEnemy();
	enemy->walk_speed = 100.0f;
	enemy->physics->aabb.size = { 16, 16 };
	enemy->physics->aabb.position.x = 6 * TILE_SIZE;
	enemy->physics->aabb.position.y = 9 * TILE_SIZE;
	enemy->sprite->animation = new Animation();
	enemy->sprite->animation->texture = ResourceManager::getTexture("wabbit_alpha");
	enemy->sprite->animation->frames.push_back(Rectangle { 0, 0, 32, 32 });

	Breakable* breakable = new Breakable(tileMap, Vector2 { 24, 9 });

	CameraController* cameraController = new CameraController();
	cameraController->player = player;
	cameraController->mode = CAM_RIGHT;

	TileAnimationController* tileAnims = new TileAnimationController(tileMap, { 4, 5, 6, 7 });
	for (int i = 0; i < 7; i++) {
	    tileAnims->tiles.push_back(Vector2 { i + 25, 10 });
	}

	PhysicsArea* lavaPit = new PhysicsArea();
	lavaPit->layer = LAYER_ENEMY;
	lavaPit->aabb.position = Vector2 { 25 * TILE_SIZE, 11 * TILE_SIZE };
	lavaPit->aabb.size = Vector2 { 7 * TILE_SIZE, 1 * TILE_SIZE };
	PhysicsServer::push(lavaPit);

	Scene* scene = new Scene();
	scene->push(tileMap);
	scene->push(player);
	scene->push(enemy);
	scene->push(breakable);
	scene->push(cameraController);
	scene->push(tileAnims);

	SceneManager::replace(scene);

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

		float dt = GetFrameTime();

		// run scene logic
		Color background = BLACK;
		if (SceneManager::current != NULL) {
		    SceneManager::current->update(dt);
			background = SceneManager::current->background;
		}
        bounds->position.x = RenderingServer::camera.target.x - 16;
        bounds->position.y = RenderingServer::camera.target.y - 16;

        // run physics
		PhysicsServer::update(dt, bounds);

		// draw game onto render target
		BeginTextureMode(target);
		ClearBackground(background);
		RenderingServer::update(dt, bounds);
		EndTextureMode();

		// draw render target
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetSrc, targetDest, targetPos, 0.0f, WHITE);
		EndDrawing();
	}

	ResourceManager::unloadResources();

	CloseWindow();
	return 0;
}
