#pragma once
#include "Entity.h"

class LivingEntity : public Entity {
	private:
		bool alive = true;
	public:
		void kill();
		virtual void onKilled() = 0;
};