#include "PhysicsRect.h"
#include "PhysicsComponent.h"
#include "PhysicsHitbox.h"
#include "SceneManager.h"

bool PhysicsRect::isOnScreen() const {
    return SceneManager::workspace->testAABB(aabb);
}

bool PhysicsRect::testCollision(float _, PhysicsComponent* collider) {
    if (PhysicsRect* rect = dynamic_cast<PhysicsRect*>(collider)) {
        return aabb.testAABB(rect->aabb);
    }
    return false;
}

void PhysicsRect::onCollision(PhysicsComponent* collider) {
    if (PhysicsHitbox* hitbox = dynamic_cast<PhysicsHitbox*>(collider)) {
        hitbox->enabled = false;
    }
}
