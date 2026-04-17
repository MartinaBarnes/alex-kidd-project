#pragma once
#include "Entity.h"
#include "PhysicsTileMap.h"
#include "RenderTileMap.h"

class TileMap : public Entity {
    public:
        PhysicsTileMap* physics;
        RenderTileMap* render;

        Vector2 findSpawnPoint(Vector2);

        TileMap();
		~TileMap();
};
