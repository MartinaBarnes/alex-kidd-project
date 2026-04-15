#include "RenderComponent.h"

class Sprite : public RenderComponent {
	private:
	    Vector2 size;
	public:
		Vector2 position;
		Texture2D* texture;
		Rectangle frame;

		bool isOnScreen(const AABB*) const override;
		void draw(float) override;
};
