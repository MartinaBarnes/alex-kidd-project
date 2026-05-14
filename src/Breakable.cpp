#include "Breakable.h"
#include "ParticleEmitter.h"
#include "RenderingServer.h"
#include "ResourceManager.h"

void Breakable::doBreak(Vector2 pos) {
    ParticleEmitter* emitter = new ParticleEmitter();
    emitter->origin = pos;
    emitter->particles = &particles;
    emitter->oneShot = true;
    emitter->active = true;
    RenderingServer::push(emitter);
    PlaySound(*ResourceManager::getSound(sound));
    onBreak(pos);
}

Breakable::Breakable(Particles newParticles) {
    particles = newParticles;
}

Breakable::Breakable(Particles newParticles, std::string newSound) : Breakable(newParticles) {
    sound = newSound;
}
