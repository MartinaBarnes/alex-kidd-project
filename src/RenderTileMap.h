#pragma once
#include "PhysicsTileMap.h"
#include "RenderComponent.h"

class RenderTileMap : public RenderComponent {
    public:
        char* tileset[64];
        int map[TILEMAP_WIDTH][TILEMAP_HEIGHT];
        AABB* bounds;

        bool isOnScreen(const AABB*) const override;
        void draw(float) override;
};
