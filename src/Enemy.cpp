#include "Enemy.h"
#include "PhysicsComponent.h"
#include "PhysicsArea.h"
#include "PhysicsHitbox.h"
#include "PhysicsServer.h"
#include "AnimatedSprite.h"
#include "RenderingServer.h"
#include "ResourceManager.h"

void Enemy::onKilled() {
    deathSprite->position = sprite->position;
    deathSprite->enabled = true;
    sprite->enabled = false;
    physics->enabled = false;
}

void Enemy::update(float dt) {
    // if we're dead, do the death sequence
    if (!alive) {
        if (deathTime < DEATH_TIME) {
            deathTime += dt;
            if (deathTime >= DEATH_TIME) {
                deathSprite->enabled = false;
                markedForDeletion = true;
            }
        }
        return;
    }

    // otherwise, check if we should die
	for (int i = 0; i < physics->colliders.size(); i++) {
		if (PhysicsHitbox* hitbox = dynamic_cast<PhysicsHitbox*>(physics->colliders[i])) {
			kill();
			return;
		}
	}

	// update sprite position
	sprite->position = physics->aabb.position;
}

Enemy::Enemy() {
    deathSprite = new AnimatedSprite();
    deathSprite->enabled = false;
    deathSprite->animation = new Animation();
    deathSprite->animation->texture = ResourceManager::getTexture("effects");
    deathSprite->animation->frames = {
        Rectangle { 0, 0, 16, 16 },
        Rectangle { 16, 0, 16, 16 }
    };
    deathSprite->frame_rate = 4.0f;
    RenderingServer::push(deathSprite);

	physics = new PhysicsCharacter();
	physics->layer = LAYER_ENEMY;
	physics->mask = LAYER_WORLD + LAYER_PLAYER;
	PhysicsServer::push(physics);

	sprite = new AnimatedSprite();
	RenderingServer::push(sprite);
}

Enemy::~Enemy() {
    RenderingServer::pop(deathSprite);
    delete deathSprite->animation;
    delete deathSprite;

	PhysicsServer::pop(physics);
	delete physics;

	RenderingServer::pop(sprite);
	delete sprite->animation;
	delete sprite;
}
