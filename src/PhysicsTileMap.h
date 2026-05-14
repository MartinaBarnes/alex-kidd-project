#pragma once
#include "PhysicsComponent.h"
#include "raylib.h"

#define TILEMAP_WIDTH   128
#define TILEMAP_HEIGHT  128
#define TILE_SIZE       16

#define PHYSTILE_AIR        0
#define PHYSTILE_SOLID      1
#define PHYSTILE_WATER      2
#define PHYSTILE_DEATHPIT   3
#define PHYSTILE_HALF       4

struct TileCoords {
    int x;
    int y;

    bool const operator==(const TileCoords &o) const {
        return x == o.x && y == o.y;
    }

    bool const operator<(const TileCoords &o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
};

/**
 * Physics tile map class.
 * Contains the physics data of a tile map.
 */
class PhysicsTileMap : public PhysicsComponent {
    public:
        short map[TILEMAP_WIDTH][TILEMAP_HEIGHT];
        std::vector<TileCoords> tilesHit; // tiles hit by a PhysicsHitbox

        bool isOnScreen() const override;
        void resetCollision() override;
        bool testCollision(float, PhysicsComponent*) override;

        void setTileMap(short[TILEMAP_HEIGHT][TILEMAP_WIDTH]);
};
