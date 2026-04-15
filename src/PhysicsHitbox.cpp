#include "PhysicsHitbox.h"

bool PhysicsHitbox::isOnScreen(const AABB* bounds) const
{
    return bounds->testAABB(aabb);
}
