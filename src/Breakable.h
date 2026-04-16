#pragma once
#include "Entity.h"
#include "PhysicsArea.h"
#include "TileMap.h"

class Breakable : public Entity {
	protected:
		PhysicsArea* physics;
	public:
		TileMap* tileMap;
		Vector2 tileCoords;

		void update(float) override;
		virtual void onBreak() {};
		void doBreak();

		Breakable(TileMap*, Vector2);
		~Breakable();
};