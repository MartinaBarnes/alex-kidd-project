#include "Pogostick.h"
#include "raylib.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"

#include <iostream>
using namespace std;

Pogostick::Pogostick()
{
    physics = new PhysicsPlayer();
    hitbox = new PhysicsHitbox();
    sprite = new AnimatedSprite();
    
    PhysicsServer::push(physics);
    PhysicsServer::push(hitbox);
    RenderingServer::push(sprite);

    physics->layer = LAYER_PLAYER;
    physics->mask = LAYER_WORLD;

    direction = DIRECTION_RIGHT;
    bouncing = false;

    //
    physics->aabb.position = { 100, 100 };
    physics->aabb.size = { 12, 35 };
    hitbox->aabb.size = { 12, 6 };

    //Animated
    Texture2D* texture = ResourceManager::getTexture("alex_pogo");
    Animation* animation = new Animation();
    animation->texture = texture;
    animation->frames = 
    {
        Rectangle {0, 0, 16, 35},
        Rectangle {18, 0, 16, 35},
        Rectangle {36, 0, 16, 35}
    };

    sprite->animation = animation;
}

Pogostick::~Pogostick()
{
    delete physics;
    delete hitbox;
    delete sprite->animation;
    delete sprite;
}

void Pogostick::update(float delta)
{
    cout << physics->aabb.position.x << " " << physics->aabb.position.y << endl;

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

    //Gravity


    //Bounce
    if (physics->onGround)
    {
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

    //HITBOX sprite
    hitbox->aabb.position = physics->aabb.position;
    hitbox->aabb.position.y += physics->aabb.size.y;
}

void Pogostick :: onKilled() { }