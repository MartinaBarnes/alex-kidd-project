#include "PhysicsArea.h"

bool PhysicsArea::isOnScreen(const AABB* bounds) const
{
    return bounds->testAABB(aabb);
}
