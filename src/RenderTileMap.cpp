#include "RenderTileMap.h"
#include "ResourceManager.h"

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
            DrawTextureRec(*texture, tiles[map[u + i][v + j]], Vector2 { x + i * TILE_SIZE, y + j * TILE_SIZE }, WHITE);
        }
    }
    /**Texture2D texture = ResourceManager::getTexture(tileset->texture);
    for (int i=0; i<bounds->size.x / TILE_SIZE; i++) {
        for (int j=0; j<bounds->size.y / TILE_SIZE; j++) {
            int tile = map[u + i][v + j];
            int tileY = tile / tileset->hTiles;
            int tileX = tile - tileY * tileset->hTiles;
            DrawTextureRec(texture, Rectangle { tileX, tileY, tileX * TILE_SIZE, tileY * TILE_SIZE }, Vector2 { x + i * TILE_SIZE, y + j * TILE_SIZE }, WHITE);
        }
    }*/
    /**int u = bounds->position.x / TILE_SIZE;
    int v = bounds->position.y / TILE_SIZE;
    float x = u * TILE_SIZE;
    float y = v * TILE_SIZE;
    for (int i=0; i<bounds->size.x / TILE_SIZE; i++) {
        for (int j=0; j<bounds->size.y / TILE_SIZE; j++) {
            DrawTexture(ResourceManager::getTexture(tileset[map[u + i][v + j]]), x + i * TILE_SIZE, y + j * TILE_SIZE, WHITE);
        }
        }*/
}
