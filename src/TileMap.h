#pragma once
#include "Entity.h"
#include "PhysicsTileMap.h"
#include "RenderTileMap.h"

class TileMap : public Entity {
    public:
        PhysicsTileMap* physics;
        RenderTileMap* render;

        TileMap();
		~TileMap();
};
