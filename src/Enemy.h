#pragma once
#include "LivingEntity.h"
#include "PhysicsCharacter.h"
#include "AnimatedSprite.h"

/**
 * Enemy class.
 * Base for all enemies in the game.
 * It implements physics, a sprite, and an effect upon dying.
 */
class Enemy : public LivingEntity {
    protected:
        const float DEATH_TIME = 0.5f;
        AnimatedSprite* deathSprite;
        float deathTime = 0.0f;
	public:
		PhysicsCharacter* physics;
		AnimatedSprite* sprite;

		void update(float) override;
		void onKilled() override;

		Enemy();
		~Enemy();
};
