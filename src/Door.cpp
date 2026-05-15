#include "Door.h"

#include "raylib.h"

Door::Door(Vector2 pos, Player* player)
{
    this->player = player;

    hitbox = new PhysicsHitbox();

    hitbox->aabb.position = pos;
    hitbox->aabb.size = { 32, 64 };

    sprite = new AnimatedSprite();

    sprite->position = pos;
}

Door::~Door()
{
    delete hitbox;
    delete sprite;
}

void Door::update(float delta)
{

    bool playerInside =
        hitbox->aabb.testAABB(player->physics->aabb);

    if (state == IDLE)
    {
        if (
            playerInside &&
            IsKeyPressed(KEY_UP)
            )
        {
            // bloquear jugador
            player->enabled = false;

            // empezar entrada
            state = ENTERING;

            timer = 0.5f;
        }
    }

    else if (state == ENTERING)
    {
        timer -= delta;

        // aquí luego pondrás sprite abierta

        if (timer <= 0.0f)
        {
            // mover jugador dentro
            player->physics->aabb.position =
            {
                120,
                120
            };

            state = INSIDE_WAIT;

            timer = 1.0f;
        }
    }

    // =========================
    // ESPERA DENTRO
    // =========================

    else if (state == INSIDE_WAIT)
    {
        timer -= delta;

        if (timer <= 0.0f)
        {
            // devolver control
            player->enabled = true;

            state = INSIDE;
        }
    }
}





