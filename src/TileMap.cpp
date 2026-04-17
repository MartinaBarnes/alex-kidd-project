#include "TileMap.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include <cmath>

Vector2 TileMap::findSpawnPoint(Vector2 origin) {
    int x = std::ceil(origin.x / TILE_SIZE);
    int y = std::ceil(origin.y / TILE_SIZE);
    for (int i = x; i < std::min(x + 16, TILEMAP_WIDTH); i++) {
        for (int j = y; j < std::min(y + 10, TILEMAP_HEIGHT - 2); j++) {
            if (physics->map[i][j] || physics->map[i][j + 1] || !physics->map[i][j + 2]) {
                continue;
            }
            return Vector2 { i * TILE_SIZE, j * TILE_SIZE };
        }
    }
    return origin;
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
