#include "RenderComponent.h"

/**
 * Game over label class.
 * Draws the game over title and the player's score.
 */
class GameOverLabel : public RenderComponent {
	public:
		int score = 0;
		bool isOnScreen() const override;
		void draw(float) override;
};
