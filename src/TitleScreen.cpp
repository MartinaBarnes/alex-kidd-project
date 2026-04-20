#include "TitleScreen.h"
#include "SceneManager.h"
#include "SceneFactory.h"

void TitleScreen::update(float _) {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) {
        SceneManager::replace(SceneFactory::intro1());
        return;
    }
}
