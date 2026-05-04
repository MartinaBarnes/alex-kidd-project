#include "RenderTileMap.h"
#include "PhysicsTileMap.h"
#include "SceneManager.h"
#include <cmath>

void RenderTileMap::draw(float _) {
    int u = SceneManager::workspace->position.x / TILE_SIZE;
    int v = SceneManager::workspace->position.y / TILE_SIZE;
    float x = u * TILE_SIZE;
    float y = v * TILE_SIZE;
    for (int i=0; i<=SceneManager::workspace->size.x / TILE_SIZE; i++) {
        for (int j=0; j<=SceneManager::workspace->size.y / TILE_SIZE; j++) {
            int tile = map[std::min(u + i, TILEMAP_WIDTH)][std::min(v + j, TILEMAP_HEIGHT)];
            if (tile < 0) {
                continue;
            }
            DrawTextureRec(*texture, tiles[tile], Vector2{ (float)(x + i * TILE_SIZE), (float)(y + j * TILE_SIZE) }, WHITE);
        }
    }
}
