#include "Enemy.h"
#include "PhysicsComponent.h"
#include "PhysicsServer.h"
#include "PhysicsHitbox.h"

void Enemy::onKilled() {
    scene->pop(this);
}

void Enemy::update(float dt) {
	for (int i = 0; i < physics->colliders.size(); i++) {
		if (PhysicsHitbox* hitbox = dynamic_cast<PhysicsHitbox*>(physics->colliders[i])) {
		    /*if (!hitbox->active) {
				continue;
			}*/
			kill();
			return;
		}
	}
	test += dt;
	physics->aabb.position.x += dt;
	if (test >= 1.0f) {
	    test = 0.0f;
		physics->aabb.position.x -= 10.0f;
	}
}

Enemy::Enemy() {
	physics = new PhysicsCharacter();
	physics->layer = LAYER_ENEMY;
	physics->mask = LAYER_PLAYER;
	PhysicsServer::push(physics);
}

Enemy::~Enemy() {
	PhysicsServer::pop(physics);
	delete physics;
}
