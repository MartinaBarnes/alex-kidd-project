#include "HoppingEnemy.h"

void HoppingEnemy::update(float dt) {
    WanderingEnemy::update(dt);
    if (!physics->awake) {
        return;
    }
    if (physics->onGround) {
        physics->velocity.y -= bounceForce;
    } else {
        physics->velocity.y += gravity;
    }
}
