#include "ParticleEmitter.h"
#include "RenderingServer.h"
#include "SceneManager.h"
#include <cmath>

bool ParticleEmitter::isOnScreen(const AABB* _) const {
    return active;
}

void ParticleEmitter::draw(float dt) {
    if (time >= LIFE_TIME) {
        time = 0.0f;
        active = false;
        if (oneShot) {
            RenderingServer::pop(this);
            delete this;
        }
        return;
    }
    float x = time * VELOCITY_X;
    float y = std::pow(time, 2.0f) * VELOCITY_Y;
    DrawTextureRec(*texture, frame, Vector2 { origin.x + x, origin.y + y }, WHITE);
    DrawTextureRec(*texture, frame, Vector2 { origin.x - x, origin.y + y }, WHITE);
    DrawTextureRec(*texture, frame, Vector2 { origin.x + x, origin.y + y + frame.height }, WHITE);
    DrawTextureRec(*texture, frame, Vector2 { origin.x - x, origin.y + y + frame.height }, WHITE);
    if (SceneManager::pause && !pausable) {
	    return;
	}
    time += dt;
}
