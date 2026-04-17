#include "Player.h"
#include "PhysicsCharacter.h"
#include "PhysicsComponent.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "ResourceManager.h"
#include "raylib.h"
#include <algorithm>

#define ANIM_IDLE 0
#define ANIM_WALK 1
#define ANIM_JUMP 2
#define ANIM_ATTACK 3
#define ANIM_CROUCH 4
#define ANIM_DEATH 5

void Player::onKilled() {
    alive = false;
    sprite->animation = &animations[ANIM_DEATH];
}

void Player::decelerate(float dt) {
    if (physics->velocity.x < 0.0f) {
        physics->velocity.x = std::min(physics->velocity.x + walk_deceleration * dt, 0.0f);
    } else {
        physics->velocity.x = std::max(physics->velocity.x - walk_deceleration * dt, 0.0f);
    }
}

void Player::update(float dt) {
    if (!alive) {

        return;
    }

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
        sprite->animation = &animations[ANIM_JUMP];
    } else {
        bool last_crouching = crouching;
        crouching = IsKeyDown(KEY_DOWN);
        if (last_crouching != crouching) {
            if (last_crouching) {
                physics->aabb.position.y -= 8.0f;
            } else {
                physics->aabb.position.y += 8.0f;
            }
        }
        if (crouching) {
            sprite->animation = &animations[ANIM_CROUCH];
        } else {
            if (physics->velocity.x != 0.0f) {
                sprite->animation = &animations[ANIM_WALK];
            } else {
                sprite->animation = &animations[ANIM_IDLE];
            }
        }
    }

    sprite->position = physics->aabb.position;
    if (crouching) {
        sprite->position.y -= 4.0f;
    }

    if (!physics->onGround || !attacking) {
        if (crouching) {
            decelerate(dt);
        } else {
            if (IsKeyDown(KEY_RIGHT)) {
                direction = DIRECTION_RIGHT;
                physics->velocity.x = std::min(physics->velocity.x + accel * dt, speed);
            } else if (IsKeyDown(KEY_LEFT)) {
                direction = DIRECTION_LEFT;
                physics->velocity.x = std::max(physics->velocity.x - accel * dt, -speed);
            } else {
                decelerate(dt);
            }
        }
    }

    sprite->flipped = direction == DIRECTION_LEFT;

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
        sprite->animation = &animations[ANIM_ATTACK];
        attack_time += dt;
        if (attack_time >= max_attack_time) {
            attacking = false;
        }
        if (sprite->flipped) {
            sprite->position.x -= 8;
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
    hitbox->enabled = attacking;
}

Player::Player() {
	physics = new PhysicsCharacter();
	physics->layer = LAYER_PLAYER;
	physics->mask = LAYER_WORLD + LAYER_ENEMY + LAYER_BOUNDS;
	physics->aabb = AABB(0, 0, 16, 24);
	PhysicsServer::push(physics);

	hitbox = new PhysicsArea();
	hitbox->layer = LAYER_PLAYER;
	hitbox->mask = LAYER_ENEMY + LAYER_BREAKABLE;
	hitbox->aabb = AABB(0, 0, 16, 16);
	PhysicsServer::push(hitbox);

    Texture2D* texture = ResourceManager::getTexture("alex");
    animations[ANIM_IDLE] = Animation { texture, { { 1, 28, 16, 24 } } };
    animations[ANIM_WALK] = Animation { texture, {
        { 1, 2, 16, 24 },
        { 18, 2, 16, 24 },
        { 35, 2, 16, 24 },
        { 52, 2, 16, 24 }
    } };
    animations[ANIM_JUMP] = Animation { texture, { { 44, 29, 16, 24 } } };
    animations[ANIM_ATTACK] = Animation { texture, { { 19, 28, 24, 24 } } };
    animations[ANIM_CROUCH] = Animation { texture, { { 62, 32, 15, 20 } } };
    animations[ANIM_DEATH] = Animation { texture, {
        { 1, 131, 16, 24 },
        { 19, 131, 16, 24 },
        { 37, 131, 16, 24 }
    } };

    sprite = new AnimatedSprite();
    sprite->animation = &animations[0];
    RenderingServer::push(sprite);
}

Player::~Player() {
	PhysicsServer::pop(physics);
	delete physics;

    PhysicsServer::pop(hitbox);
    delete hitbox;

    RenderingServer::pop(sprite);
    delete sprite;
}
