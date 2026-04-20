#pragma once
#include "LivingEntity.h"
#include "PhysicsCharacter.h"
#include "PhysicsHitbox.h"
#include "AnimatedSprite.h"
#include "TileMap.h"

#define DIRECTION_RIGHT 1.0f
#define DIRECTION_LEFT -1.0f

/**
 * Player class.
 * Implements all player related systems, such as movement, combat
 * and death sequence.
 */
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
        bool respawning = false;

		void decelerate(float);
		void crouch(bool);
	public:
	    const float WALK_SPEED          = 100.0f;
		const float WALK_ACCELERATION   = 900.0f;
		const float WALK_DECELERATION   = 500.0f;
		const float MAX_JUMP_TIME       = 0.4f;
		const float JUMP_FORCE          = 120.0f;
		const float AIR_ACCELERATION    = 150.0f;
		const float GRAVITY             = 800.0f;
		const float ATTACK_DURATION     = 0.25f;
		const float DEATH_ANIM_SPEED    = 80.0f;
		const float DEATH_ANIM_DELAY    = 0.5f;

        PhysicsCharacter* physics;
        PhysicsHitbox* hitbox;
        AnimatedSprite* sprite;
		TileMap* tileMap;

		void update(float) override;
		void onKilled() override;

		Player();
		~Player();
};
