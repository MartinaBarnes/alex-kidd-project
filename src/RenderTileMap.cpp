#include "RenderTileMap.h"
#include "PhysicsTileMap.h"
#include "ResourceManager.h"
#include <iostream>

bool RenderTileMap::isOnScreen(const AABB* _) const {
    return true;
}

void RenderTileMap::draw(float _) {
    int u = bounds->position.x / TILE_SIZE;
    int v = bounds->position.y / TILE_SIZE;
    float x = u * TILE_SIZE;
    float y = v * TILE_SIZE;
    for (int i=0; i<bounds->size.x / TILE_SIZE; i++) {
        for (int j=0; j<bounds->size.y / TILE_SIZE; j++) {
            DrawTexture(ResourceManager::getTexture(tileset[map[u + i][v + j]]), x + i * TILE_SIZE, y + j * TILE_SIZE, WHITE);
        }
    }
}
