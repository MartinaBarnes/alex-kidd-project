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
		float time = 0.0f;
	public:
	    float duration = 5.0f;

		void update(float) override;

		GameOverScreen();
		~GameOverScreen();
};
