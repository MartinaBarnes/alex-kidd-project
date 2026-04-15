#include "Enemy.h"
#include "PhysicsComponent.h"
#include "PhysicsHitbox.h"
#include "PhysicsServer.h"
#include "AnimatedSprite.h"
#include "RenderingServer.h"

void Enemy::onKilled() {
    scene->pop(this);
    delete this;
}

void Enemy::update(float dt) {
	for (int i = 0; i < physics->colliders.size(); i++) {
		if (PhysicsHitbox* hitbox = dynamic_cast<PhysicsHitbox*>(physics->colliders[i])) {
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
