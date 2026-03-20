#include "Player.h"
#include "PhysicsCharacter.h"
#include "PhysicsServer.h"
#include "raylib.h"

void Player::update(float dt) {
	if (physics->onWall) {
		velocity.x = 0.0f;
	}

	if (!physics->onGround) {
		velocity.y += 5.0f * dt;
	} else {
		velocity.y = 0.0f;
	}

	if (IsKeyDown(KEY_RIGHT)) {
		velocity.x = 100.0f * dt;
	}
	else if (IsKeyDown(KEY_LEFT)) {
		velocity.x = -100.0f * dt;
	}
	else {
		velocity.x = 0.0f;
	}

	if (IsKeyDown(KEY_UP) and physics->onGround) {
		velocity.y -= 200.0f * dt;
	}

	physics->aabb.position.x += velocity.x;
	physics->aabb.position.y += velocity.y;
}

Player::Player() {
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	physics = new PhysicsCharacter();
	physics->layer = 2;
	physics->mask = 1;
	physics->aabb = AABB(0, 0, 16, 16);
	physics->owner = this;
	PhysicsServer::add(physics);
}

Player::~Player() {
	PhysicsServer::remove(physics);
	delete physics;
}