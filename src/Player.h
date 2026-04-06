#pragma once
#include "Entity.h"
#include "PhysicsCharacter.h"

class Player : public Entity
{
    private:
        float jump_time = 0.0f;
        bool jumping = false;
	public:
	    float acceleration = 1000.0f;
	    float walk_speed = 100.0f;
		float jump_force = 80.0f;
		float max_jump_time = 0.5f;
		float air_acceleration = 200.0f;
		float gravity = 400.0f;

		PhysicsCharacter* physics;

		void update(float) override;

		Player();
		~Player();
};
