#pragma once
#include "LivingEntity.h"
#include "PhysicsCharacter.h"
#include "AnimatedSprite.h"

class Enemy : public LivingEntity {
	public:
		PhysicsCharacter* physics;
		AnimatedSprite* sprite;

		void update(float) override;
		void onKilled() override;

		Enemy();
		~Enemy();
};
