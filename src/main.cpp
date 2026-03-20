#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "physicsserver.h"
#include "renderingserver.h"
#include "physicscharacter.h"
#include "physicstilemap.h"
#include "scene.h"

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
	PhysicsCharacter* box0 = new PhysicsCharacter();
	PhysicsCharacter* box1 = new PhysicsCharacter();

	map->layer = 2;
	map->mask = 0;
	map->map[28][12] = true;

	box0->layer = 1;
	box0->mask = 2;
	box0->aabb.position.x = 300.0f;
	box0->aabb.position.y = 200.0f;
	box0->aabb.size.x = 32.0f;
	box0->aabb.size.y = 32.0f;

	box1->layer = 2;
	box1->mask = 0;
	box1->aabb.position.x = 400.0f;
	box1->aabb.position.y = 200.0f;
	box1->aabb.size.x = 32.0f;
	box1->aabb.size.y = 32.0f;

	PhysicsServer::components.push_back(map);
	PhysicsServer::components.push_back(box0);
	PhysicsServer::components.push_back(box1);

	Scene* scene = new Scene();
	AABB* viewport = new AABB( 0, 0, 1280, 800 );
	bool reverse = false;

	// game loop
	while (!WindowShouldClose()) // run the loop until the user presses ESCAPE or presses the Close button on the window
	{
	    if (reverse) {
			if (box0->aabb.position.x < 300.0f) {
			    reverse = false;
			} else {
			    box0->aabb.position.x -= 1.0f;
			}
		} else {
		    if (box0->aabb.position.x > 500.0f ) {
				reverse = true;
			} else {
			    box0->aabb.position.x += 1.0f;
			}
		}

        PhysicsServer::update(viewport);
        scene->update(GetFrameTime());

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		RenderingServer::update(viewport);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);

		if (box0->colliders.size() > 0) {
		    DrawTexture(wabbit, box0->aabb.position.x, box0->aabb.position.y, RED);
		} else {
		    DrawTexture(wabbit, box0->aabb.position.x, box0->aabb.position.y, WHITE);
		}

		DrawTexture(wabbit, 28 * 16, 12 * 16, GREEN);

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
