#pragma once
#include "LivingEntity.h"
#include "PhysicsCharacter.h"
#include "PhysicsArea.h"
#include "AnimatedSprite.h"

#define DIRECTION_RIGHT 1.0f
#define DIRECTION_LEFT -1.0f

class Player : public LivingEntity
{
    protected:
        float direction = DIRECTION_RIGHT;
        bool crouching = false;
        bool jumping = false;
        float jump_time = 0.0f;
        bool attacking = false;
        float attack_time = 0.0f;
		Animation animations[6];

		void decelerate(float);
	public:
	    bool alive = true;
	    float walk_speed = 100.0f;
	    float walk_acceleration = 900.0f;
		float walk_deceleration = 600.0f;
		float max_jump_time = 0.5f;
		float jump_force = 80.0f;
		float air_acceleration = 300.0f;
		float gravity = 500.0f;
		float max_attack_time = 0.25f;
		float hitbox_offset = 8.0f;
		float death_sprite_speed = 120.0f;

		PhysicsCharacter* physics;
		PhysicsArea* hitbox;
		AnimatedSprite* sprite;

		void update(float) override;
		void onKilled() override;

		Player();
		~Player();
};
