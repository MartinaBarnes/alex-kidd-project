#include "Pogostick.h"
#include "raylib.h"

Pogostick::Pogostick()
{
    physics = new PhysicsCharacter();
    hitbox = new PhysicsHitbox();
    sprite = new AnimatedSprite();

    direction = DIRECTION_RIGHT;
    bouncing = false;

    //
    physics->aabb.position = { 100, 100 };
    physics->aabb.size = { 12, 24 };
    hitbox->aabb.size = { 12, 6 };

    //Animated
    Texture2D* texture = ResourceManager::getTexture("alex_pogo");
    Animation* animation = new Animation();
    animation->texture = texture;
    animation->frames = {
        Rectangle {},
        Rectangle {},
        Rectangle {}
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
    physics->velocity.y += GRAVITY * delta;

    //Bounce
    if (physics->onGround)
    {
        physics->velocity.y = -BOUNCE_FORCE;

        if (IsKeyDown(KEY_UP))
        {
            physics->velocity.y = -BOUNCE_FORCE * 2;
        }
    }

    //Sprites
    sprite->position = physics->aabb.position;
    sprite->flipped = (direction == DIRECTION_LEFT);

    //HITBOX sprite
    hitbox->aabb.position = physics->aabb.position;
    hitbox->aabb.position.y += physics->aabb.size.y;
}