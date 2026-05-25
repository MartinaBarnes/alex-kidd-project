#include "Pogostick.h"
#include "raylib.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"

Pogostick::Pogostick()
{
    direction = DIRECTION_RIGHT;

    physics = new PhysicsPlayer();
    physics->aabb.position = { 100, 100 };
    physics->aabb.size = { 12, 35 };
    physics->layer = LAYER_PLAYER;
    physics->mask = LAYER_WORLD + LAYER_ENEMY;
    PhysicsServer::push(physics);

    hitbox = new PhysicsHitbox();
    hitbox->aabb.size = { 12, 4 };
    hitbox->layer = LAYER_PLAYER;
	hitbox->mask = LAYER_WORLD + LAYER_ENEMY + LAYER_BREAKABLE;
	hitbox->oneShot = true;
	hitbox->enabled = false;
    PhysicsServer::push(hitbox);

    sprite = new AnimatedSprite();
    sprite->running = false;
    sprite->oneShot = true;

    //Animated
    Texture2D* texture = ResourceManager::getTexture("alex_pogo");
    Animation* animation = new Animation();
    animation->texture = texture;
    animation->frames =
    {
        Rectangle { 36, 0, 16, 35 },
        Rectangle { 18, 0, 16, 35 },
        Rectangle { 0, 0, 16, 35 },
    };

    sprite->animation = animation;
    RenderingServer::push(sprite);
}

Pogostick::~Pogostick()
{
    PhysicsServer::pop(physics);
    delete physics;

    PhysicsServer::pop(hitbox);
    delete hitbox;

    RenderingServer::pop(sprite);
    delete sprite->animation;
    delete sprite;
}

Vector2 Pogostick::getPosition() {
    return physics->aabb.position;
}

Vector2 Pogostick::getVelocity() {
    return physics->velocity;
}

void Pogostick::update(float delta)
{
    if (physics->inDeathPit) {
        kill(); // destroy pogostick after touching a death pit
    } else {
        if (hitbox->colliders.empty()) {
            for (int i = 0; i < physics->colliders.size(); i++) {
                if (physics->colliders[i]->layer & LAYER_ENEMY) {
                    kill(); // destroy pogostick after touching an enemy
                    return;
                }
            }
        }
    }

    //Movement
    float move = 0.0f;

    if (IsKeyDown(KEY_LEFT))
    {
        move -= 1.0f;
        direction = DIRECTION_LEFT;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        move += 1.0f;
        direction = DIRECTION_RIGHT;
    }

    physics->velocity.x = move * MOVE_SPEED;

    //Bounce
    if (physics->onGround || !hitbox->colliders.empty())
    {
        sprite->start();
        physics->velocity.y = -BOUNCE_FORCE;

        if (IsKeyDown(KEY_UP))
        {
            physics->velocity.y = -BOUNCE_FORCE * 2;
        }
    }
    else
    {
        physics->velocity.y += GRAVITY * delta;
    }

    //Sprites
    sprite->position = physics->aabb.position;
    sprite->flipped = (direction == DIRECTION_LEFT);

    //HITBOX
    hitbox->aabb.position = physics->aabb.position;
    hitbox->aabb.position.y += physics->aabb.size.y - hitbox->aabb.size.y + 2.0f + GRAVITY * delta;
    hitbox->enabled = physics->velocity.y >= 0.0f;
}

void Pogostick::onKilled() {
    driver->invulnerability = 1.0f;
    driver->vehicle = NULL;
    markedForDeletion = true;
}
