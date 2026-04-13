#include "AnimatedSprite.h"

bool AnimatedSprite::isOnScreen(const AABB* bounds) const {
	return bounds->testAABB(aabb);
}

void AnimatedSprite::draw(float dt) {
	float duration = 1.0f / frame_rate;
	if (frame > animation->frames.size()) {
		frame = 0;
	}
	Rectangle frameRec = animation->frames[frame];
	DrawTextureRec(*animation->texture, frameRec, position, WHITE);
	aabb.position = position;
	aabb.size.x = frameRec.width;
	aabb.size.y = frameRec.height;
	frame_rate += dt;
	if (next_frame >= duration) {
		frame += 1;
		next_frame -= duration;
	}
}