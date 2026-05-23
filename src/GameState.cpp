#include "GameState.h"

int GameState::lives = 3;
int GameState::baums = 0;

void GameState::reset() {
    GameState::lives = 3;
    GameState::baums = 0;
}
