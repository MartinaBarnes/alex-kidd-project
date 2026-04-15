#include "Sprite.h"

bool Sprite::isOnScreen(const AABB* bounds) const {
    AABB aabb;
    aabb.position = position;
    aabb.size = size;
	return bounds->testAABB(aabb);
}

void Sprite::draw(float _) {
	DrawTextureRec(*texture, frame, position, WHITE);
	size = { frame.width, frame.height };
}
