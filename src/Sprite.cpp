#include "Sprite.h"

bool Sprite::isOnScreen(const AABB* bounds) const {
	return bounds->testAABB(aabb);
}

void Sprite::draw(float _) {
	DrawTextureRec(*texture, frame, position, WHITE);
	aabb.position = position;
	aabb.size.x = frame.width;
	aabb.size.y = frame.height;
}