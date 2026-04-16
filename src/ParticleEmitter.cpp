#include "ParticleEmitter.h"
#include <cmath>

bool ParticleEmitter::isOnScreen(const AABB* _) const {
    return active;
}

void ParticleEmitter::draw(float dt) {
    if (time >= LIFE_TIME) {
        time = 0.0f;
        active = false;
        return;
    }
    float x = time * VELOCITY_X;
    float y = std::pow(time, 2.0f) * VELOCITY_Y;
    DrawTextureRec(*texture, frame, Vector2 { origin.x + x, origin.y + y }, WHITE);
    DrawTextureRec(*texture, frame, Vector2 { origin.x - x, origin.y + y }, WHITE);
    DrawTextureRec(*texture, frame, Vector2 { origin.x + x, origin.y + y + frame.height }, WHITE);
    DrawTextureRec(*texture, frame, Vector2 { origin.x - x, origin.y + y + frame.height }, WHITE);
    time += dt;
}
