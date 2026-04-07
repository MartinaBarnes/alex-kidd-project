#include "PhysicsHitbox.h"

bool PhysicsHitbox::isOnScreen(const AABB* viewport) const
{
    return true;
}

bool PhysicsHitbox::testCollision(float dt, PhysicsComponent* collider)
{
    return false;
}
