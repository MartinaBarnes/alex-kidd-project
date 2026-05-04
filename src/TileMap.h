#pragma once
#include "Entity.h"
#include "PhysicsTileMap.h"
#include "RenderTileMap.h"
#include "ParticleEmitter.h"
#include <map>

/**
 * Tile map class.
 * Handles the physics and rendering data of a tile map.
 */
class TileMap : public Entity {
    public:
        PhysicsTileMap* physics;
        RenderTileMap* render;
        std::map<TileCoords, bool> breakables;
        std::map<int, Particles*> particles;

        Vector2 findSpawnPoint(Vector2);
        void setTilePair(int, int, int, int);
        void update(float) override;

        TileMap();
		~TileMap();
};
