#pragma once
#include "Entity.h"
#include "GameOverLabel.h"

/**
 * Game over screen.
 * Shows the game over label.
 */
class GameOverScreen : public Entity {
	protected:
		GameOverLabel* label;
	public:
		GameOverScreen();
		~GameOverScreen();
};
