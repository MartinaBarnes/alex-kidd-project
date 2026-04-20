#include "StatusScreen.h"
#include "ResourceManager.h"

bool StatusScreen::isOnScreen() const {
    return true;
}

void StatusScreen::draw(float dt) {
    DrawTexutre(*ResourceManager::getTexture("ui_map0"), 0, 0, WHITE);
}
