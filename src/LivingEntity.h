#pragma once
#include "Entity.h"

class LivingEntity : public Entity {
	public:
	    bool alive = true;
		void kill();
		virtual void onKilled() = 0;
};
