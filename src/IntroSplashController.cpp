#include "IntroSplashController.h"
#include "RenderingServer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SceneFactory.h"
#include "Sprite.h"

void IntroSplashController::update(float dt) {
    time += dt;
    sprite->enabled = time > 0.5 && time < 3.75;
    if (time > 4.0f) {
        SceneManager::queued = SceneFactory::title();
    }
}

IntroSplashController::IntroSplashController() {
    sprite = new Sprite();
    sprite->texture = ResourceManager::getTexture("ui_intro");
    sprite->frame = Rectangle { 0, 0, GAME_WIDTH, GAME_HEIGHT };
    RenderingServer::pushOverlay(sprite);
}

IntroSplashController::~IntroSplashController() {
    RenderingServer::popOverlay(sprite);
    delete sprite;
}
