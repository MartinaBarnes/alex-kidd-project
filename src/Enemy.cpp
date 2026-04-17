#include "Enemy.h"
#include "PhysicsComponent.h"
#include "PhysicsArea.h"
#include "PhysicsServer.h"
#include "AnimatedSprite.h"
#include "RenderingServer.h"

void Enemy::onKilled() {
    scene->pop(this);
    delete this;
}

void Enemy::update(float _) {
	for (int i = 0; i < physics->colliders.size(); i++) {
		if (PhysicsArea* hitbox = dynamic_cast<PhysicsArea*>(physics->colliders[i])) {
			kill();
			return;
		}
	}
	sprite->position = physics->aabb.position;
}

Enemy::Enemy() {
	physics = new PhysicsCharacter();
	physics->layer = LAYER_ENEMY;
	physics->mask = LAYER_WORLD + LAYER_PLAYER;
	PhysicsServer::push(physics);

	sprite = new AnimatedSprite();
	RenderingServer::push(sprite);
}

Enemy::~Enemy() {
	PhysicsServer::pop(physics);
	delete physics;

	RenderingServer::pop(sprite);
	delete sprite;
}
