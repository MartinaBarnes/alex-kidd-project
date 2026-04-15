#include "PhysicsSolid.h"

bool PhysicsSolid::isOnScreen(const AABB* bounds) const
{
    return bounds->testAABB(aabb);
}
