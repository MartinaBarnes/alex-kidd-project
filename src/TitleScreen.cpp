#include "TitleScreen.h"
#include "SceneManager.h"
#include "SceneFactory.h"

void TitleScreen::update(float _) {
    if (IsKeyPressed(0)) {
        SceneManager::replace(SceneFactory::intro1());
        return;
    }
}
