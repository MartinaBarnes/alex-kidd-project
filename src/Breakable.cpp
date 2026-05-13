#include "Breakable.h"

static Particles DEFAULT_BREAK_PARTICLES    = Particles { ResourceManager::getTexture("tiles"), { Rectangle { 112, 16, 7, 7 } } };
static std::string DEFAULT_BREAK_SOUND      = "break";

void Breakable::doBreak(Vector2 pos) {
    // TODO: summon particle emitter and play break sound
}
