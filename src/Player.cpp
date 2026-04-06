#include "Player.h"
#include "PhysicsCharacter.h"
#include "PhysicsServer.h"
#include "raylib.h"
#include <algorithm>

void Player::update(float dt) {
    float speed = walk_speed;
    float accel = acceleration;

    if (!physics->onGround) {
        accel = air_acceleration;
    }

    if (IsKeyDown(KEY_RIGHT)) {
        physics->velocity.x = std::min(physics->velocity.x + accel * dt, speed);
    } else if (IsKeyDown(KEY_LEFT)) {
        physics->velocity.x = std::max(physics->velocity.x - accel * dt, -speed);
    } else {
        if (physics->velocity.x < 0.0f) {
            physics->velocity.x = std::min(physics->velocity.x + acceleration * dt, 0.0f);
        } else {
            physics->velocity.x = std::max(physics->velocity.x - acceleration * dt, 0.0f);
        }
    }

    if (jumping) {
        if (jump_time >= max_jump_time || !IsKeyDown(KEY_UP)) {
            jumping = false;
            jump_time = 0.0f;
        } else {
            jump_time += dt;
            physics->velocity.y = -jump_force;
        }
    } else {
        if (!physics->onGround) {
            physics->velocity.y += gravity * dt;
        } else {
            if (IsKeyDown(KEY_UP)) {
                jumping = true;
            }
        }
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
