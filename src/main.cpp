#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "PhysicsTileMap.h"
#include "Player.h"
#include "Scene.h"

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Alex Kidd in Miracle World");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	PhysicsTileMap* map = new PhysicsTileMap();
	map->layer = 1;
	for (int i = 0; i < 128; i++) {
		map->map[i][32] = true;
	}
	PhysicsServer::components.push_back(map);

	Player* player = new Player();

	AABB* viewport = new AABB(0, 0, 1280, 800);
	Scene* scene = new Scene();
	scene->entities.push_back(player);

	// game loop
	while (!WindowShouldClose()) // run the loop until the user presses ESCAPE or presses the Close button on the window
	{
        scene->update(GetFrameTime());
		PhysicsServer::update(viewport);

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		RenderingServer::update(viewport);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);
		DrawTexture(wabbit, player->physics->aabb.position.x, player->physics->aabb.position.y, WHITE);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
