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
        Animation animations[6];
        float direction = DIRECTION_RIGHT;
        bool crouching = false;
        bool jumping = false;
        float jump_time = 0.0f;
        bool attacking = false;
        float attack_time = 0.0f;
        float death_time = 0.0f;

		void decelerate(float);
	public:
	    const float WALK_SPEED          = 100.0f;
		const float WALK_ACCELERATION   = 900.0f;
		const float WALK_DECELERATION   = 600.0f;
		const float MAX_JUMP_TIME       = 0.5f;
		const float JUMP_FORCE          = 80.0f;
		const float AIR_ACCELERATION    = 300.0f;
		const float GRAVITY             = 500.0f;
		const float ATTACK_DURATION     = 0.25f;
		const float DEATH_ANIM_SPEED    = 80.0f;
		const float DEATH_ANIM_DELAY    = 1.0f;

	    bool alive = true;

		PhysicsCharacter* physics;
		PhysicsArea* hitbox;
		AnimatedSprite* sprite;

		void update(float) override;
		void onKilled() override;

		Player();
		~Player();
};
