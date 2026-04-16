#include "WanderingEnemy.h"

void WanderingEnemy::update(float dt) {
    if (physics->onWall) {
        direction *= -1;
    }
    physics->velocity.x = walk_speed * direction;
    Enemy::update(dt);
}
