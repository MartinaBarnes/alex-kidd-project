#include "Player.h"
#include "PhysicsCharacter.h"
#include "PhysicsComponent.h"
#include "ResourceManager.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "SceneManager.h"
#include "GameState.h"
#include "SceneFactory.h"
#include "raylib.h"
#include <algorithm>

#define ANIM_IDLE 0
#define ANIM_WALK 1
#define ANIM_JUMP 2
#define ANIM_ATTACK 3
#define ANIM_CROUCH 4
#define ANIM_DEATH 5

void Player::onKilled() {
    GameState::lives--;
    pausable = true;
    death_time = 0.0f;
    attacking = false;
    hitbox->enabled = false;
    physics->velocity = Vector2 { 0, 0 };
    SceneManager::pause = true;
    StopMusicStream(*scene->music);
}

void Player::decelerate(float dt) {
    if (physics->velocity.x < 0.0f) {
        physics->velocity.x = std::min(physics->velocity.x + WALK_DECELERATION * dt, 0.0f);
    } else {
        physics->velocity.x = std::max(physics->velocity.x - WALK_DECELERATION * dt, 0.0f);
    }
}

void Player::crouch(bool crouch) {
    if (crouching == crouch) {
        return;
    }
    if (crouching) {
        physics->aabb.position.y -= 8.0f; // HACK: should use a variable or constant
    } else {
        physics->aabb.position.y += 8.0f; // HACK
    }
    crouching = crouch;
}

void Player::update(float dt) {
    // run the death sequence when dead
    if (!alive) {
        // wait a bit before respawning
        if (respawning) {
            if (death_time < DEATH_ANIM_DELAY) {
                death_time += dt;
                if (death_time >= DEATH_ANIM_DELAY) {
                    if (GameState::lives <= 0) {
                        SceneManager::replace(SceneFactory::gameOver());
                        return;
                    }
                    alive = true;
                    pausable = false;
                    sprite->pausable = false;
                    physics->aabb.position = tileMap->findSpawnPoint(Vector2 { RenderingServer::camera.target.x + 1, RenderingServer::camera.target.y }); // HACK
                    physics->aabb.position.y += 8.0f; // HACK: make it start on the ground
                    physics->onGround = true;
                    respawning = false;
                    SceneManager::pause = false;
                    RenderingServer::visible = true;
                    StopSound(*ResourceManager::getSound("death"));
                    PlayMusicStream(*scene->music);
                }
            }
            return;
        }
        // after dying, freeze the screen a bit before showing the sequence
        if (death_time < DEATH_ANIM_DELAY) {
            death_time += dt;
            if (death_time >= DEATH_ANIM_DELAY) {
                sprite->pausable = true;
                sprite->animation = &animations[ANIM_DEATH];
                PlaySound(*ResourceManager::getSound("death"));
            }
        } else {
            // the death sequence lasts until the sprite exits the screen
            if (sprite->position.y + sprite->animation->frames[0].height > RenderingServer::camera.target.y) {
                sprite->position.y -= DEATH_ANIM_SPEED * dt;
            } else {
                death_time = 0.0f;
                respawning = true;
                RenderingServer::visible = false;
            }
        }
        return;
    }

    if (physics->inDeathPit) {
        kill(); // kill player after touching a death pit
    } else {
        for (int i = 0; i < physics->colliders.size(); i++) {
            if (physics->colliders[i]->layer & LAYER_ENEMY) {
                kill(); // kill player after touching an enemy
                return;
            }
        }
    }

    float speed = WALK_SPEED;
    float accel = WALK_ACCELERATION;

    // are we jumping or crouching?
    if (!physics->onGround) {
        accel = AIR_ACCELERATION;
        sprite->animation = &animations[ANIM_JUMP];
        crouch(false);
    } else {
        crouch(IsKeyDown(KEY_DOWN));
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

    // update sprite position
    sprite->position = physics->aabb.position;
    if (crouching) {
        sprite->position.y -= 4.0f; // HACK: the sprite height and the intended collision height are different
    }

    // ground movement
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

    // jumping and falling
    if (jumping) {
        if (jump_time >= MAX_JUMP_TIME || !IsKeyDown(KEY_UP) || physics->onCeiling) {
            jumping = false;
            jump_time = 0.0f;
        } else {
            jump_time += dt;
            physics->velocity.y = -JUMP_FORCE;
        }
    } else {
        if (!physics->onGround) {
            physics->velocity.y += GRAVITY * dt;
        } else {
            if (IsKeyPressed(KEY_UP) && !attacking) {
                jumping = true;
                PlaySound(*ResourceManager::getSound("jump"));
            }
        }
    }

    // punching
    if (attacking) {
        sprite->animation = &animations[ANIM_ATTACK];
        attack_time += dt;
        if (attack_time >= ATTACK_DURATION) {
            attacking = false;
            hitbox->enabled = false;
        }
        if (sprite->flipped) {
            sprite->position.x -= 8; // HACK: offset the punching animation (for being wider than the rest)
        }
    } else {
        if (IsKeyPressed(KEY_SPACE)) {
            attack_time = 0.0f;
            attacking = true;
            hitbox->enabled = true;
            if (physics->onGround) {
                physics->velocity.x = 0.0f;
            }
            PlaySound(*ResourceManager::getSound("punch"));
        }
    }

    // place the punch hitbox on the side the player is facing
    hitbox->aabb.position.x = physics->aabb.position.x + physics->aabb.size.x / 2.0f - hitbox->aabb.size.x / 2.0f + hitbox->aabb.size.x * direction;
    hitbox->aabb.position.y = physics->aabb.position.y + physics->aabb.size.y - hitbox->aabb.size.y;
}

Player::Player() {
	physics = new PhysicsCharacter();
	physics->layer = LAYER_PLAYER;
	physics->mask = LAYER_WORLD + LAYER_ENEMY + LAYER_BOUNDS;
	physics->aabb = AABB(0, 0, 16, 24);
	PhysicsServer::push(physics);

	hitbox = new PhysicsHitbox();
	hitbox->layer = LAYER_PLAYER;
	hitbox->mask = LAYER_ENEMY + LAYER_BREAKABLE;
	hitbox->aabb = AABB(0, 0, 8, 16);
	hitbox->enabled = false;
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
        { 1, 131, 17, 24 },
        { 19, 131, 17, 24 },
        { 37, 131, 17, 24 }
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
