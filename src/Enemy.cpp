#include "Enemy.h"
#include "PhysicsServer.h"
#include "PhysicsHitbox.h"

void Enemy::update(float _) {
	for (int i = 0; i < physics->colliders.size(); i++) {
		if (PhysicsHitbox* character = dynamic_cast<PhysicsHitbox*>(physics->colliders[i])) {
			kill();
			return;
		}
	}
}

void Enemy::onKilled() {

}

Enemy::Enemy() {
	physics = new PhysicsCharacter();
	PhysicsServer::push(physics);
}

Enemy::~Enemy() {
	PhysicsServer::pop(physics);
	delete physics;
}