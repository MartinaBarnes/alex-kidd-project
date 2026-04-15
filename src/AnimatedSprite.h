#pragma once
#include "RenderComponent.h"
#include "raylib.h"
#include <vector>

struct Animation {
	Texture2D* texture;
	std::vector<Rectangle> frames;
};

class AnimatedSprite : public RenderComponent {
	private:
		int frame = 0;
		float next_frame = 0.0f;
		Vector2 size;
	public:
	    bool flipped;
		Vector2 position;
		float frame_rate = 0.0f;
		Animation* animation;

		bool isOnScreen(const AABB*) const override;
		void draw(float) override;
};
