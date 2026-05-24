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
	SetWindowState(FLAG_WINDOW_MAXIMIZED);

	RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
	Rectangle targetSrc = Rectangle { 0, 0, GAME_WIDTH, -GAME_HEIGHT };
	Rectangle targetDest = Rectangle { 0 };
	Vector2 targetPos = Vector2 { 0 };

	SceneManager::queued = SCENE_INTRO;

	while (!WindowShouldClose()) // run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// if we have a new queued scene, change it
		if (SceneManager::queued > SCENE_NONE) {
		    if (SceneManager::scene) {
				delete SceneManager::scene;
			}
			switch (SceneManager::queued) {
			    case SCENE_INTRO:
					SceneManager::scene = SceneFactory::intro();
					break;
				case SCENE_TITLE:
				    SceneManager::scene = SceneFactory::title();
					break;
				case SCENE_PREVIEW1:
				    SceneManager::scene = SceneFactory::preview1();
					break;
				case SCENE_LEVEL1:
				    SceneManager::scene = SceneFactory::level1();
					break;
				case SCENE_PREVIEW2:
				    SceneManager::scene = SceneFactory::preview2();
					break;
				case SCENE_LEVEL2:
				    SceneManager::scene = SceneFactory::level2();
					break;
				case SCENE_GAMEOVER:
				    SceneManager::scene = SceneFactory::gameOver();
					break;
				case SCENE_SHOP:
				    SceneManager::scene = SceneFactory::shop();
					break;
			}
			SceneManager::queued = SCENE_NONE;

			SceneManager::pause = false;
			RenderingServer::camera.target = Vector2{ 0, 0 };
			RenderingServer::visible = true;

		}

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
		if (SceneManager::scene) {
			background = SceneManager::scene->background;
            SceneManager::scene->update(dt);
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
