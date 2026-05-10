#pragma once
#include "RenderComponent.h"

#define TILEMAP_WIDTH 128
#define TILEMAP_HEIGHT 128
#define TILE_SIZE 16

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

        void setTileSet(Rectangle[64]);
        void setTileMap(short[TILEMAP_WIDTH][TILEMAP_HEIGHT]);
};
