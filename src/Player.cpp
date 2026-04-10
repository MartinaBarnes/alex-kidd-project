#include "Player.h"
#include "PhysicsCharacter.h"
#include "PhysicsComponent.h"
#include "PhysicsHitbox.h"
#include "PhysicsServer.h"
#include "raylib.h"
#include <algorithm>
#include <iostream>

void Player::onKilled() {
    scene->pop(this);
}

void Player::update(float dt) {
    for (int i = 0; i < physics->colliders.size(); i++) {
        if (PhysicsCharacter* character = dynamic_cast<PhysicsCharacter*>(physics->colliders[i])) {
            kill();
            return;
        }
    }

    float speed = walk_speed;
    float accel = walk_acceleration;

    if (!physics->onGround) {
        accel = air_acceleration;
    }

    if (!attacking || physics->onGround) {
        if (IsKeyDown(KEY_RIGHT)) {
            direction = DIRECTION_RIGHT;
            physics->velocity.x = std::min(physics->velocity.x + accel * dt, speed);
        } else if (IsKeyDown(KEY_LEFT)) {
            direction = DIRECTION_LEFT;
            physics->velocity.x = std::max(physics->velocity.x - accel * dt, -speed);
        } else {
            if (physics->velocity.x < 0.0f) {
                physics->velocity.x = std::min(physics->velocity.x + walk_acceleration * dt, 0.0f);
            } else {
                physics->velocity.x = std::max(physics->velocity.x - walk_acceleration * dt, 0.0f);
            }
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
            if (IsKeyDown(KEY_UP) && !attacking) {
                jumping = true;
            }
        }
    }

    if (attacking) {
        attack_time += dt;
        if (attack_time >= max_attack_time) {
            attacking = false;
        }
    } else {
        if (IsKeyPressed(KEY_SPACE)) {
            attack_time = 0.0f;
            attacking = true;
            if (physics->onGround) {
                physics->velocity.x = 0.0f;
            }
        }
    }

    hitbox->aabb.position.x = physics->aabb.position.x + physics->aabb.size.x / 2.0f - hitbox->aabb.size.x / 2.0f + hitbox_offset * direction;
    hitbox->aabb.position.y = physics->aabb.position.y + physics->aabb.size.y / 2.0f - hitbox->aabb.size.y / 2.0f;
    std::cout << hitbox->aabb.position.x << " " << hitbox->aabb.position.y << std::endl;
    hitbox->active = attacking;
}

Player::Player() {
	physics = new PhysicsCharacter();
	physics->layer = LAYER_PLAYER;
	physics->mask = LAYER_WORLD + LAYER_ENEMY;
	physics->aabb = AABB(0, 0, 16, 32);
	physics->owner = this;
	PhysicsServer::push(physics);

	hitbox = new PhysicsHitbox();
	hitbox->layer = LAYER_PLAYER;
	hitbox->mask = LAYER_ENEMY + LAYER_BREAKABLE;
	hitbox->aabb = AABB(0, 0, 16, 16);
	PhysicsServer::push(hitbox);
}

Player::~Player() {
	PhysicsServer::pop(physics);
	delete physics;

    PhysicsServer::pop(hitbox);
    delete hitbox;
}
