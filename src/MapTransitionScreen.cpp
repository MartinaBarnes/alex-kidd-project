#include "MapTransitionScreen.h"
#include "AnimatedSprite.h"
#include "RenderingServer.h"
#include "SceneManager.h"
#include "SceneFactory.h"
#include "ResourceManager.h"
#include <cmath>

void MapTransitionScreen::update(float dt) {
    if (time >= duration + delay - 0.2f) {
        RenderingServer::visible = false; // briefly make the screen blank
    }
    if (time >= duration + delay) {
        SceneManager::replace(SceneFactory::level1());
        return;
    }
    preview->open = std::min(time / duration, 1.0f);
    time += dt;
}

MapTransitionScreen::MapTransitionScreen() {
    preview = new MapPreview();
    preview->position = Vector2{ 28, 24 };
    preview->arrowPosition = Vector2 { 140, 72 };
    RenderingServer::pushOverlay(preview);

    alex = new AnimatedSprite();
    alex->position = Vector2{ 218, 126 };
    alex->animation = new Animation();
    alex->animation->texture = ResourceManager::getTexture("alex");
	alex->animation->frames = {
	    Rectangle { 1, 340, 31, 45 },
		Rectangle { 34, 340, 31, 45 }
	};
	alex->frame_rate = 2.0f;
    RenderingServer::pushOverlay(alex);
}

MapTransitionScreen::~MapTransitionScreen() {
    RenderingServer::popOverlay(preview);
    delete preview;

    RenderingServer::popOverlay(alex);
    delete alex->animation;
    delete alex;
}
