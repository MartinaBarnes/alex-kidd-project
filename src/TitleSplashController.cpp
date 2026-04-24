#include "TitleSplashController.h"
#include "SceneManager.h"
#include "SceneFactory.h"
#include "RenderingServer.h"
#include "ResourceManager.h"

void TitleSplashController::update(float _) {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) {
        StopSound(*ResourceManager::getSound("title_screen"));
        SceneManager::replace(SceneFactory::preview1());
        return;
    }
}

TitleSplashController::TitleSplashController() {
    label = new TitleScreenLabel();
    RenderingServer::pushOverlay(label);
}

TitleSplashController::~TitleSplashController() {
    RenderingServer::popOverlay(label);
    delete label;
}
