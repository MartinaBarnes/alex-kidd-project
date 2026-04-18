#include "WanderingEnemy.h"
#include <cmath>

void WanderingEnemy::update(float dt) {
    Enemy::update(dt);
    if (!physics->awake) {
        return;
    }
    if (physics->onWall || (wander_distance > 0.0f && wandered >= wander_distance)) {
        direction *= -1;
        wandered = 0.0f;
        sprite->flipped = direction == 1;
    }
    physics->velocity.x = walk_speed * direction;
    wandered += std::abs(physics->velocity.x) * dt;
}
