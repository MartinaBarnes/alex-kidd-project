#pragma once
#include "Entity.h"
#include "PhysicsArea.h"
#include "Sprite.h"

class BaumPickup : public Entity {
	protected:
	    const float DISAPPEAR_TIME = 5.0f;
		const int SMALL_BAUM_COUNT = 10;
		const int LARGE_BAUM_COUNT = 20;
	public:
		PhysicsArea* physics;
		Sprite* sprite;
		int baums;
		bool temp = false;
		float time = 0.0f;

		void update(float) override;

		BaumPickup(Vector2, bool, bool = false);
		~BaumPickup();
};
