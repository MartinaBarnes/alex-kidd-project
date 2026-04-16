#include "PhysicsSolid.h"
#include "PhysicsArea.h"
#include "PhysicsCharacter.h"

bool PhysicsSolid::isOnScreen(const AABB* bounds) const
{
    return bounds->testAABB(aabb);
}

bool PhysicsSolid::testCollision(float _, PhysicsComponent* collider) {
    if (PhysicsArea* area = dynamic_cast<PhysicsArea*>(collider)) {
        return area->aabb.testAABB(aabb);
    }
    if (PhysicsSolid* solid = dynamic_cast<PhysicsSolid*>(collider)) {
        return solid->aabb.testAABB(aabb);
    }
    if (PhysicsCharacter* character = dynamic_cast<PhysicsCharacter*>(collider)) {
        return character->aabb.testAABB(aabb);
    }
    return false;
}