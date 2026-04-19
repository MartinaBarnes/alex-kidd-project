#pragma once
#include "Entity.h"

/**
 * Living entity class.
 * Base for all living entities that can die.
 */
class LivingEntity : public Entity {
	public:
	    bool alive = true;
		void kill();
		virtual void onKilled() = 0;
};
