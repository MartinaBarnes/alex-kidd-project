#pragma once
#include "Vehicle.h"
#include "PhysicsCharacter.h"
#include "PhysicsHitbox.h"
#include "AnimatedSprite.h"

#define DIRECTION_RIGHT 1.0f
#define DIRECTION_LEFT -1.0f

class Pogostick : public Vehicle
{
protected:

    // Dirección
    float direction = DIRECTION_RIGHT;

    // Estado
    bool bouncing = false;

public:

    // Movimiento
    const float MOVE_SPEED = 180.0f;
    const float AIR_ACCEL = 500.0f;
    const float GRAVITY = 900.0f;
    const float BOUNCE_FORCE = 350.0f;
    const float MAX_FALL_SPEED = 700.0f;

    // Componentes
    PhysicsCharacter* physics;
    PhysicsHitbox* hitbox;
    AnimatedSprite* sprite;

    // Función propia del Pogostick
    void update(float delta);

    //Constructor
    Pogostick();

    //Destructor
    ~Pogostick();
};