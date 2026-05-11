#include "Pogostick.h"
#include "raylib.h"
#include "AnimatedSprite.h"

void Pogostick::update(float delta)
{
    // =========================
    // INPUT HORIZONTAL
    // =========================

    float movement = 0.0f;

    if (IsKeyDown(KEY_A))
    {
        movement -= 1.0f;
        direction = DIRECTION_LEFT;
    }

    if (IsKeyDown(KEY_D))
    {
        movement += 1.0f;
        direction = DIRECTION_RIGHT;
    }

    // Movimiento horizontal
    physics->velocity.x = movement * MOVE_SPEED;

    // =========================
    // GRAVEDAD
    // =========================

    physics->velocity.y += GRAVITY * delta;

    // Limitar velocidad máxima de caída
    if (physics->velocity.y > MAX_FALL_SPEED)
    {
        physics->velocity.y = MAX_FALL_SPEED;
    }

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
}