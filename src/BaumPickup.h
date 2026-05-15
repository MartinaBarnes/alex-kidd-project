#pragma once
#include "Entity.h"
#include "PhysicsArea.h"
#include "Sprite.h"

class BaumPickup : public Entity {
	protected:
		const int SMALL_BAUM_COUNT = 10;
		const int LARGE_BAUM_COUNT = 20;
	public:
		PhysicsArea* physics;
		Sprite* sprite;
		int baums;

		void update(float) override;

		BaumPickup(Vector2, bool);
		~BaumPickup();
};