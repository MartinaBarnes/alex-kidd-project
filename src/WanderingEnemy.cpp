#include "WanderingEnemy.h"
#include <cmath>

void WanderingEnemy::update(float dt) {
    Enemy::update(dt);

    // if we're out of focus, do not move
    if (!physics->awake) {
        return;
    }

    // if we've hit a wall or finished our wandering route, turn back
    if (physics->onWall || (wander_distance > 0.0f && wandered >= wander_distance)) {
        direction *= -1;
        wandered = 0.0f;
        sprite->flipped = direction == 1;
    }

    // move
    physics->velocity.x = walk_speed * direction;
    wandered += std::abs(physics->velocity.x) * dt;
}
