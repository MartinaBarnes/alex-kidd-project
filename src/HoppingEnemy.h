#pragma once
#include "WanderingEnemy.h"

/**
 * Hopping enemy class.
 * An enemy that moves around while bouncing.
 */
class HoppingEnemy : public WanderingEnemy {
    public:
        float bounceForce = 64.0f;
        float gravity = 4.0f;
        void update(float) override;
};
