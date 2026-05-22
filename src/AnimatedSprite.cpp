#include "AnimatedSprite.h"
#include "SceneManager.h"
#include "RenderingServer.h"
#include <cmath>

bool AnimatedSprite::isOnScreen() const {
    AABB aabb;
    aabb.position = position;
    aabb.size = size;
	return SceneManager::workspace->testAABB(aabb);
}

void AnimatedSprite::draw(float dt) {
    if (!running) {
        return;
    }

    // if we reached the end of animation (or we changed to a shorter animation) reset
	if (frame >= animation->frames.size()) {
		frame = 0;

		if (oneShot) {
		    running = false;
		}
	}

	// get the frame to draw
	Rectangle src = animation->frames[frame];
	if (flipped) {
	    src.width = -src.width;
	}

	// get scissor rectangle to draw
	Rectangle dest = Rectangle { position.x + scissor.x, position.y + scissor.y, std::abs(src.width) - scissor.width, src.height - scissor.height };
	if (!onOverlay) {
	    dest.x -= RenderingServer::camera.target.x;
		dest.y -= RenderingServer::camera.target.y;
	}

	// draw frame
	BeginScissorMode(std::round(dest.x), std::round(dest.y), dest.width, dest.height);
	DrawTextureRec(*animation->texture, src, position, WHITE);
	EndScissorMode();

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
	size = { dest.width, dest.height }; // store last frame size
}
