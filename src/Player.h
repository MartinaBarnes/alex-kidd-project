#pragma once
#include "Entity.h"
#include "PhysicsCharacter.h"

class Player : public Entity
{
	public:
		PhysicsCharacter* physics;

		void update(float) override;

		Player();
		~Player();
};

