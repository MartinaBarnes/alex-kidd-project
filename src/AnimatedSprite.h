#pragma once
#include "RenderComponent.h"
#include "raylib.h"
#include <vector>

/**
 * Animation struct.
 * Contains texture and frames information for an animation.
 */
struct Animation {
	Texture2D* texture;
	std::vector<Rectangle> frames;
};

/**
 * Animated sprite class.
 * Runs and draws a selectable animation.
 */
class AnimatedSprite : public RenderComponent {
	private:
		int frame = 0;
		float next_frame = 0.0f;
		Vector2 size; // last frame size (for screen boundaries detection)
	public:
	    bool flipped;
		Vector2 position;
		float frame_rate = 12.0f;
		Animation* animation;

		bool isOnScreen() const override;
		void draw(float) override;
};
