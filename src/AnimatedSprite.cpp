#include "AnimatedSprite.h"

bool AnimatedSprite::isOnScreen(const AABB* bounds) const {
	return bounds->testAABB(aabb);
}

void AnimatedSprite::draw(float dt) {
	float frame_time = 1.0f / frame_rate;
	if (frame >= animation->frames.size()) {
		frame = 0;
	}
	Rectangle source = animation->frames[frame];
	if (flipped) {
	    source.width = -source.width;
	}
	DrawTextureRec(*animation->texture, source, position, WHITE);
	aabb.position = position;
	aabb.size = { source.width, source.height };
	next_frame += dt;
	if (next_frame >= frame_time) {
		frame += 1;
		next_frame -= frame_time;
	}
}
