#include "AnimatedSprite.h"
#include "SceneManager.h"

bool AnimatedSprite::isOnScreen() const {
    AABB aabb;
    aabb.position = position;
    aabb.size = size;
	return SceneManager::workspace->testAABB(aabb);
}

void AnimatedSprite::draw(float dt) {
    // if we reached the end of animation (or we changed to a shorter animation) reset
	if (frame >= animation->frames.size()) {
		frame = 0;
	}

	// get the frame to draw
	Rectangle src = animation->frames[frame];
	if (flipped) {
	    src.width = -src.width;
	}

	// draw frame
	DrawTextureRec(*animation->texture, src, position, WHITE);

	// run animation (if not paused or pausable)
	if (SceneManager::pause && !pausable) {
	    return;
	}
	next_frame += dt;
	float frame_time = 1.0f / frame_rate;
	if (next_frame >= frame_time) {
		frame++;
		next_frame -= frame_time;
	}
	size = { src.width, src.height }; // store last frame size
}
