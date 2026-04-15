#include "WanderingEnemy.h"

void WanderingEnemy::update(float dt) {
    Enemy::update(dt);
    if (physics->onWall) {
        direction *= -1;
    }
    physics->velocity.x = walk_speed * direction;
}
