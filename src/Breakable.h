#pragma once
#include "Entity.h"
#include "PhysicsArea.h"
#include "ParticleEmitter.h"
#include "TileMap.h"

class Breakable : public Entity {
	protected:
		PhysicsArea* physics;
		ParticleEmitter* particles;
	public:
		TileMap* tileMap;
		Vector2 tileCoords;

		void update(float) override;
		virtual void onBreak() {};
		void doBreak();

		Breakable(TileMap*, Vector2);
		Breakable(TileMap*, Vector2, Texture2D*, Rectangle);
		~Breakable();
};
