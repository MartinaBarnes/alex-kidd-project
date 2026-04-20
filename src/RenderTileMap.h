#pragma once
#include "RenderComponent.h"
#include "PhysicsTileMap.h"

/**
 * Render tile map class.
 * Draws the tiles of a tile map.
 */
class RenderTileMap : public RenderComponent {
    public:
        Texture2D* texture; // texture to draw the tiles from
        Rectangle tiles[64]; // sections of the texture to use
        short map[TILEMAP_WIDTH][TILEMAP_HEIGHT];

        void draw(float) override;
};
