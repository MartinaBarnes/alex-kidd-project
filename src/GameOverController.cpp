#include "GameOverController.h"
#include "RenderingServer.h"
#include "SceneManager.h"
#include "SceneFactory.h"

void GameOverController::update(float dt) {
    if (time >= duration) {
        SceneManager::replace(SceneFactory::title());
        return;
    }
    time += dt;
}

GameOverController::GameOverController() {
	label = new GameOverLabel();
	RenderingServer::pushOverlay(label);
}

GameOverController::~GameOverController() {
	RenderingServer::popOverlay(label);
	delete label;
}
