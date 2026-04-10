#pragma once
#include "LivingEntity.h"
#include "PhysicsCharacter.h"

class Enemy : public LivingEntity {
	public:
		PhysicsCharacter* physics;

		void update(float) override;
		void onKilled() override;

		Enemy();
		~Enemy();
};