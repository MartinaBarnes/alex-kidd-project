#include "Breakable.h"
#include "ParticleEmitter.h"
#include "RenderingServer.h"
#include "ResourceManager.h"
#include "Scene.h"

void Breakable::doBreak(Scene* scene, Vector2 position) {
    ParticleEmitter* emitter = new ParticleEmitter();
    emitter->origin = position;
    emitter->particles = &particles;
    emitter->oneShot = true;
    emitter->active = true;
    RenderingServer::push(emitter);
    PlaySound(*ResourceManager::getSound(sound));
    onBreak(scene, position);
}

Breakable::Breakable(Particles newParticles) {
    particles = newParticles;
}

Breakable::Breakable(Particles newParticles, std::string newSound) : Breakable(newParticles) {
    sound = newSound;
}
