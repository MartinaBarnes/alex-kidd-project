#include "Player.h"
#include "PhysicsCharacter.h"
#include "PhysicsServer.h"
#include "raylib.h"

void Player::update(float dt) {
	if (!physics->onGround) {
		physics->velocity.y += 400.0f * dt;
	} else if (IsKeyDown(KEY_UP) && physics->onGround) {
		physics->velocity.y = -150.0f;
	}

	if (IsKeyDown(KEY_RIGHT)) {
		physics->velocity.x = 100.0f;
	}
	else if (IsKeyDown(KEY_LEFT)) {
		physics->velocity.x = -100.0f;
	}
	else {
		physics->velocity.x = 0.0f;
	}
}

Player::Player() {
	physics = new PhysicsCharacter();
	physics->layer = 2;
	physics->mask = 1;
	physics->aabb = AABB(0, 0, 16, 32);
	physics->owner = this;
	PhysicsServer::push(physics);
}

Player::~Player() {
	PhysicsServer::pop(physics);
	delete physics;
}
