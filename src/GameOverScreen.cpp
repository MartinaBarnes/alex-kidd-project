#include "GameOverScreen.h"
#include "RenderingServer.h"
#include <iostream>

GameOverScreen::GameOverScreen() {
	label = new GameOverLabel();
	RenderingServer::pushOverlay(label);
}

GameOverScreen::~GameOverScreen() {
	RenderingServer::popOverlay(label);
	delete label;
}