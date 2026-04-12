#pragma once
#include "RenderComponent.h"
#include "PhysicsTileMap.h"

class RenderTileMap : public RenderComponent {
    public:
        Texture2D* texture;
        Rectangle tiles[64];
        int map[TILEMAP_WIDTH][TILEMAP_HEIGHT];
        AABB* bounds;

        bool isOnScreen(const AABB*) const override;
        void draw(float) override;
};
