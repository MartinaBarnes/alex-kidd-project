#pragma once
#include "Entity.h"
#include "PhysicsTileMap.h"
#include "RenderTileMap.h"

/**
 * Tile map class.
 * Handles the physics and rendering data of a tile map.
 */
class TileMap : public Entity {
    public:
        PhysicsTileMap* physics;
        RenderTileMap* render;

        Vector2 findSpawnPoint(Vector2);
        void setTilePair(int, int, int, int);

        TileMap();
		~TileMap();
};
