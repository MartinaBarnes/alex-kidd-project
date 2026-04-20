#include "GameOverScreen.h"
#include "RenderingServer.h"
#include "SceneManager.h"
#include "SceneFactory.h"

void GameOverScreen::update(float dt) {
    if (time >= duration) {
        SceneManager::replace(SceneFactory::intro1());
        return;
    }
    time += dt;
}

GameOverScreen::GameOverScreen() {
	label = new GameOverLabel();
	RenderingServer::pushOverlay(label);
}

GameOverScreen::~GameOverScreen() {
	RenderingServer::popOverlay(label);
	delete label;
}
