#include "RenderComponent.h"

class GameOverLabel : public RenderComponent {
	public:
		int score = 0;
		bool isOnScreen() const override;
		void draw(float) override;
};