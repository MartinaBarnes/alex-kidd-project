#pragma once
#include "Entity.h"
#include "GameOverLabel.h"

class GameOverScreen : public Entity {
	protected:
		GameOverLabel* label;
	public:
		GameOverScreen();
		~GameOverScreen();
};