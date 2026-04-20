#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "ResourceManager.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SceneFactory.h"
#include <cmath>

int main ()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
	InitWindow(GAME_WIDTH, GAME_HEIGHT, "Alex Kidd in Miracle World");
	InitAudioDevice();
	SetTargetFPS(60);
	SetAudioStreamBufferSizeDefault(4096);
	ResourceManager::loadResources();

	RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
	Rectangle targetSrc = Rectangle { 0, 0, GAME_WIDTH, -GAME_HEIGHT };
	Rectangle targetDest = Rectangle { 0 };
	Vector2 targetPos = Vector2 { 0 };

	SceneManager::replace(SceneFactory::gameOver());

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
        SceneManager::workspace->position.x = RenderingServer::camera.target.x - 32;
        SceneManager::workspace->position.y = RenderingServer::camera.target.y - 32;

        // run physics
		PhysicsServer::update(dt);

		// draw game onto render target
		BeginTextureMode(target);
		ClearBackground(background);
		RenderingServer::update(dt);
		EndTextureMode();

		// draw render target
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, targetSrc, targetDest, targetPos, 0.0f, WHITE);
		EndDrawing();
	}

	ResourceManager::unloadResources();
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
