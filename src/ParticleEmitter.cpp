#include "ParticleEmitter.h"
#include "RenderingServer.h"
#include "SceneManager.h"
#include <cmath>

bool ParticleEmitter::isOnScreen() const {
    return active;
}

void ParticleEmitter::draw(float dt) {
    // kill the particle system when it finishes
    if (time >= LIFE_TIME) {
        time = 0.0f;
        active = false;
        if (oneShot) {
            RenderingServer::pop(this);
            delete this;
        }
        return;
    }

    // draw the particles
    float x = time * VELOCITY_X;
    float y = std::pow(time, 2.0f) * VELOCITY_Y;
    Rectangle particle2 = particles->frames[rand() % particles->frames.size()];
    Rectangle particle3 = particles->frames[rand() % particles->frames.size()];
    DrawTextureRec(*(particles->texture), particles->frames[rand() % particles->frames.size()], Vector2 { origin.x + x, origin.y + y }, WHITE);
    DrawTextureRec(*(particles->texture), particles->frames[rand() % particles->frames.size()], Vector2 { origin.x - x, origin.y + y }, WHITE);
    DrawTextureRec(*(particles->texture), particle2, Vector2 { origin.x + x, origin.y + y + particle2.height }, WHITE);
    DrawTextureRec(*(particles->texture), particle3, Vector2 { origin.x - x, origin.y + y + particle3.height }, WHITE);

    // run the timer
    if (SceneManager::pause && !pausable) {
	    return;
	}
    time += dt;
}
