#include "GameState.h"

int GameState::lives = 3;
int GameState::baums = 0;
bool GameState::shop[2] = { true, true };

void GameState::reset() {
    GameState::lives = 3;
    GameState::baums = 0;
    GameState::shop[0] = true;
    GameState::shop[1] = true;
}
