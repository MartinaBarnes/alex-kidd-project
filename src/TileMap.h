#pragma once
#include "Entity.h"
#include "PhysicsTileMap.h"
#include "RenderTileMap.h"
#include "ParticleEmitter.h"
#include "ResourceManager.h"
#include "Breakable.h"
#include <map>
#include <string>

/**
 * Tile map class.
 * Handles the physics and rendering data of a tile map.
 */
class TileMap : public Entity {
    public:
        PhysicsTileMap* physics;
        RenderTileMap* render;
        std::map<int, Breakable> breakables;

        void update(float) override;

        Vector2 findSpawnPoint(Vector2);
        void setTilePair(int, int, int, int);

        TileMap();
		~TileMap();
};
