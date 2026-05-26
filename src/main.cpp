#include "ItemPickup.h"
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "ResourceManager.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SceneFactory.h"
#include "BaumPickup.h"
#include <algorithm>

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
	    // toggle music
		if (IsKeyPressed(KEY_M)) {
		    SceneManager::music = !SceneManager::music;
			if (SceneManager::inPlayableLevel) {
			    if (SceneManager::music) {
					PlayMusicStream(*SceneManager::scene->music);
				} else {
				    StopMusicStream(*SceneManager::scene->music);
				}
			}
		}

        // scene change cheats
        if (IsKeyPressed(KEY_F9)) { // return to title screen
            SceneManager::queued = SCENE_TITLE;
        } else if (IsKeyPressed(KEY_F10)) { // jump to level 1
            SceneManager::queued = SCENE_PREVIEW1;
        } else if (IsKeyPressed(KEY_F11)) { // jump to level 2
            SceneManager::queued = SCENE_PREVIEW2;
        } /*else if (IsKeyPressed(KEY_F12)) { // jump to level's 2 shop
            SceneManager::queued = SCENE_SHOP;
        }*/

		// if we have a new queued scene, change it
		if (SceneManager::queued > SCENE_NONE) {
		    if (SceneManager::scene) {
				delete SceneManager::scene;
			}

            SceneManager::pause = false;
            RenderingServer::camera.target = Vector2{ 0, 0 };
            RenderingServer::visible = true;

			switch (SceneManager::queued) {
			    case SCENE_INTRO:
					SceneManager::inPlayableLevel = false;
					SceneManager::scene = SceneFactory::intro();
					break;
				case SCENE_TITLE:
				    SceneManager::inPlayableLevel = false;
				    SceneManager::scene = SceneFactory::title();
					break;
				case SCENE_PREVIEW1:
                    SceneManager::inPlayableLevel = false;
				    SceneManager::scene = SceneFactory::preview1();
					break;
				case SCENE_LEVEL1:
				    SceneManager::inPlayableLevel = true;
				    SceneManager::scene = SceneFactory::level1();
					break;
				case SCENE_PREVIEW2:
				    SceneManager::inPlayableLevel = false;
				    SceneManager::scene = SceneFactory::preview2();
					break;
				case SCENE_LEVEL2:
                    SceneManager::inPlayableLevel = true;
				    SceneManager::scene = SceneFactory::level2();
					break;
				case SCENE_GAMEOVER:
				    SceneManager::inPlayableLevel = false;
				    SceneManager::scene = SceneFactory::gameOver();
					break;
				case SCENE_SHOP:
				    SceneManager::inPlayableLevel = true;
				    SceneManager::scene = SceneFactory::shop();
					break;
			}
			SceneManager::queued = SCENE_NONE;

			if (SceneManager::inPlayableLevel && !SceneManager::music) {
			    StopMusicStream(*SceneManager::scene->music);
			}
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

        // gameplay cheats
        if (SceneManager::inPlayableLevel && IsCursorOnScreen()) {
            Vector2 mousePos = GetMousePosition();
            mousePos.x = RenderingServer::camera.target.x + std::clamp((mousePos.x - targetDest.x) / resScale, 0.0f, (float)GAME_WIDTH);
            mousePos.y = RenderingServer::camera.target.y + std::clamp((mousePos.y - targetDest.y) / resScale, 0.0f, (float)GAME_HEIGHT);
            if (IsKeyPressed(KEY_F1)) { // spawn extra life
                ItemPickup* extraLife = new ItemPickup();
                extraLife->item = ITEM_LIFE;
                extraLife->sprite->texture = ResourceManager::getTexture("items");
                extraLife->sprite->frame = Rectangle { 48, 0, 16, 16 };
                extraLife->placeAt(Vector2 { mousePos.x - 8.0f, mousePos.y - 8.0f });
                SceneManager::scene->push(extraLife);
            } else if (IsKeyPressed(KEY_F2)) { // spawn pogo stick
                ItemPickup* pogoStick = new ItemPickup();
                pogoStick->item = ITEM_POGOSTICK;
                pogoStick->sprite->texture = ResourceManager::getTexture("items");
                pogoStick->sprite->frame = Rectangle { 0, 16, 16, 16 };
                pogoStick->placeAt(Vector2 { mousePos.x - 8.0f, mousePos.y - 8.0f });
                SceneManager::scene->push(pogoStick);
            } else if (IsKeyPressed(KEY_F3)) { // spawn small baums bag
                SceneManager::scene->push(new BaumPickup(Vector2 { mousePos.x - 8.0f, mousePos.y - 8.0f }, false));
            } else if (IsKeyPressed(KEY_F4)) { // spawn large baums bag
                SceneManager::scene->push(new BaumPickup(Vector2 { mousePos.x - 8.0f, mousePos.y - 8.0f }, true));
            } else if (IsKeyPressed(KEY_F5)) { // spawn scorpion
                WanderingEnemy* scorpion = SceneFactory::scorpion();
                scorpion->physics->aabb.position = Vector2 { mousePos.x - 8.0f, mousePos.y - 13.0f };
                scorpion->direction = -1;
                SceneManager::scene->push(scorpion);
            } else if (IsKeyPressed(KEY_F6)) { // spawn kaicho
                WanderingEnemy* kaicho = SceneFactory::kaicho();
                kaicho->physics->aabb.position = Vector2 { mousePos.x - 12.0f, mousePos.y - 8.0f };
                kaicho->direction = -1;
                SceneManager::scene->push(kaicho);
            } else if (IsKeyPressed(KEY_F7)) { // spawn hopper
                HoppingEnemy* hopper = SceneFactory::hopper();
                hopper->physics->aabb.position = Vector2 { mousePos.x - 8.0f, mousePos.y - 8.0f };
                hopper->direction = -1;
                SceneManager::scene->push(hopper);
            }
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

		// draw render target in original resolution
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
