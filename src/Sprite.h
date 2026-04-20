#pragma once
#include "RenderComponent.h"

/**
 * Sprite class.
 * Renders a portion of a texture as a static image.
 */
class Sprite : public RenderComponent {
	private:
	    Vector2 size; // last frame size (for culling)
	public:
		Vector2 position;
		Texture2D* texture;
		Rectangle frame;

		bool isOnScreen() const override;
		void draw(float) override;
};
