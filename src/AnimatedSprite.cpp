#include "AnimatedSprite.h"

bool AnimatedSprite::isOnScreen(const AABB* bounds) const {
    AABB aabb;
    aabb.position = position;
    aabb.size = size;
	return bounds->testAABB(aabb);
}

void AnimatedSprite::draw(float dt) {
	if (frame >= animation->frames.size()) {
		frame = 0;
	}
	Rectangle src = animation->frames[frame];
	if (flipped) {
	    src.width = -src.width;
	}
	DrawTextureRec(*animation->texture, src, position, WHITE);
	next_frame += dt;
	float frame_time = 1.0f / frame_rate;
	if (next_frame >= frame_time) {
		frame += 1;
		next_frame -= frame_time;
	}
	size = { src.width, src.height };
}
