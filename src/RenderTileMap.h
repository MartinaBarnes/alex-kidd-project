#pragma once
#include "RenderComponent.h"

#define TILEMAP_WIDTH   256
#define TILEMAP_HEIGHT  128
#define TILE_SIZE       16

/**
 * Render tile map class.
 * Draws the tiles of a tile map.
 */
class RenderTileMap : public RenderComponent {
    public:
        Texture2D* texture; // texture to draw the tiles from
        Rectangle tiles[128]; // sections of the texture to use
        short map[TILEMAP_WIDTH][TILEMAP_HEIGHT];

        void draw(float) override;

        void setTileSet(Rectangle[128]);
        void setTileMap(short[TILEMAP_HEIGHT][TILEMAP_WIDTH]);
};
