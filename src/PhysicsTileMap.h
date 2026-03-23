#pragma once
#include "PhysicsComponent.h"
#include "raylib.h"

#define TILEMAP_WIDTH 128
#define TILEMAP_HEIGHT 128
#define TILE_SIZE 16.0f

class PhysicsTileMap : public PhysicsComponent {
    public:
        bool map[TILEMAP_WIDTH][TILEMAP_HEIGHT];

        bool isOnScreen(const AABB*) const override;
};
