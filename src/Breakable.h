#pragma once
#include "Entity.h"
#include "PhysicsArea.h"
#include "ParticleEmitter.h"
#include "TileMap.h"

/**
 * Breakable entity class.
 * Allows for the destruction of a tile in a TileMap.
 * It both resets a physics map and rendered map tile, while emiting a sound
 * and activating a particle system.
 */
class Breakable : public Entity {
	protected:
		PhysicsArea* physics;
		ParticleEmitter* particles;
	public:
		TileMap* tileMap;
		Vector2 tileCoords; // tile to reset
		char* sound = "break"; // breaking sound

		void update(float) override;
		virtual void onBreak() {};
		void doBreak();

		Breakable(TileMap*, Vector2);
		Breakable(TileMap*, Vector2, Texture2D*, Rectangle);
		Breakable(TileMap*, Vector2, char*);
		Breakable(TileMap*, Vector2, Texture2D*, Rectangle, char*);
		~Breakable();
};
