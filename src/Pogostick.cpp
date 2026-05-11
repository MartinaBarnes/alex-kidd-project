#include "Pogostick.h"
#include "raylib.h"

Pogostick::Pogostick()
{
    physics = new PhysicsCharacter();
    hitbox = new PhysicsHitbox();
    sprite = new AnimatedSprite();

    direction = DIRECTION_RIGHT;
    bouncing = false;

    // Inicializar posición
    physics->aabb.position = { 100, 100 };
}

Pogostick::~Pogostick()
{
    delete physics;
    delete hitbox;
    delete sprite;
}

void Pogostick::update(float delta)
{
    // =========================
    // MOVIMIENTO HORIZONTAL
    // =========================

    float move = 0.0f;

    if (IsKeyDown(KEY_A))
    {
        move -= 1.0f;
        direction = DIRECTION_LEFT;
    }

    if (IsKeyDown(KEY_D))
    {
        move += 1.0f;
        direction = DIRECTION_RIGHT;
    }

    physics->velocity.x = move * MOVE_SPEED;

    // =========================
    // GRAVEDAD
    // =========================

    physics->velocity.y += GRAVITY * delta;

    if (physics->velocity.y > MAX_FALL_SPEED)
        physics->velocity.y = MAX_FALL_SPEED;

    // =========================
    // REBOTE AUTOMÁTICO
    // =========================

    if (physics->onGround && physics->velocity.y >= 0)
    {
        physics->velocity.y = -BOUNCE_FORCE;
    }

    // =========================
    // SPRITE
    // =========================

    sprite->position = physics->aabb.position;
    sprite->flipped = (direction == DIRECTION_LEFT);

    // HITBOX sincronizada
    hitbox->aabb.position = physics->aabb.position;
}