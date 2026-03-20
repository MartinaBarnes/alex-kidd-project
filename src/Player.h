#pragma once
#include "Entity.h"
#include "PhysicsCharacter.h"

class Player : public Entity
{
	public:
		PhysicsCharacter* physics;
		Vector2 velocity;

		void update(float) override;

		Player();
		~Player();
};

