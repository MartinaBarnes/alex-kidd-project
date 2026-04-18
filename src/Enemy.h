#pragma once
#include "LivingEntity.h"
#include "PhysicsCharacter.h"
#include "AnimatedSprite.h"

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
