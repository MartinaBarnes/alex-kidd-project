#include "TileMap.h"
#include "PhysicsServer.h"
#include "PhysicsTileMap.h"
#include "RenderingServer.h"
#include <cmath>

Vector2 TileMap::findSpawnPoint(Vector2 origin) {
    int x = std::ceil(origin.x / TILE_SIZE);
    int y = std::ceil(origin.y / TILE_SIZE);
    for (int i = x; i < std::min(x + 16, TILEMAP_WIDTH); i++) {
        for (int j = y; j < std::min(y + 10, TILEMAP_HEIGHT - 2); j++) {
            if (physics->map[i][j] != PHYSTILE_AIR || physics->map[i][j + 1] != PHYSTILE_AIR || physics->map[i][j + 2] != PHYSTILE_SOLID) {
                continue;
            }
            return Vector2 { (float)(i * TILE_SIZE), (float)(j * TILE_SIZE) };
        }
    }
    return origin;
}

void TileMap::setTilePair(int x, int y, int physTile, int tile) {
    physics->map[x][y] = physTile;
    render->map[x][y] = tile;
}

TileMap::TileMap() {
    physics = new PhysicsTileMap();
    physics->layer = LAYER_WORLD;
    PhysicsServer::push(physics);

    render = new RenderTileMap();
    RenderingServer::push(render);
}

TileMap::~TileMap() {
    PhysicsServer::pop(physics);
    delete physics;

    RenderingServer::pop(render);
    delete render;
}
