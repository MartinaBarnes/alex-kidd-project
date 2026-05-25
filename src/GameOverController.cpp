#include "GameOverController.h"
#include "RenderingServer.h"
#include "SceneManager.h"
#include "SceneFactory.h"
#include "GameState.h"

void GameOverController::update(float dt) {
    if (time >= duration) {
        SceneManager::queued = SCENE_TITLE;
        return;
    }
    time += dt;
}

GameOverController::GameOverController() {
	label = new GameOverLabel();
	label->score = GameState::score;
	RenderingServer::pushOverlay(label);
}

GameOverController::~GameOverController() {
	RenderingServer::popOverlay(label);
	delete label;
}
