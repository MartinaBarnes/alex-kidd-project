#include "Player.h"
#include "PhysicsCharacter.h"
#include "PhysicsServer.h"
#include "raylib.h"

void Player::update(float dt) {
	if (physics->onWall) {
		physics->velocity.x = 0.0f;
	}

	if (!physics->onGround) {
		physics->velocity.y += 5.0f * dt;
	} else {
		physics->velocity.y = 0.0f;
	}

	if (IsKeyDown(KEY_RIGHT)) {
		physics->velocity.x = 100.0f * dt;
	}
	else if (IsKeyDown(KEY_LEFT)) {
		physics->velocity.x = -100.0f * dt;
	}
	else {
		physics->velocity.x = 0.0f;
	}

	if (IsKeyDown(KEY_UP) && physics->onGround) {
		physics->velocity.y -= 200.0f * dt;
	}
}

Player::Player() {
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