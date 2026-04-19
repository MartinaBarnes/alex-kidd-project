#include "Sprite.h"
#include "SceneManager.h"

bool Sprite::isOnScreen() const {
    AABB aabb;
    aabb.position = position;
    aabb.size = size;
	return SceneManager::workspace->testAABB(aabb);
}

void Sprite::draw(float _) {
	DrawTextureRec(*texture, frame, position, WHITE);
	size = { frame.width, frame.height };
}
