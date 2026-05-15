#include "TileMap.h"
#include "PhysicsServer.h"
#include "PhysicsTileMap.h"
#include "RenderingServer.h"
#include <cmath>

void TileMap::update(float _) {
    if (!physics) {
        return;
    }
    for (int i = 0; i < physics->tilesHit.size(); i++) {
        TileCoords coords = physics->tilesHit[i];
        int tile = render->map[coords.x][coords.y];
        if (breakables.find(tile) == breakables.end()) {
            continue;
        }
        setTilePair(coords.x, coords.y, PHYSTILE_AIR, 0);
        breakables[tile]->doBreak(scene, Vector2 { (float)coords.x * TILE_SIZE, (float)coords.y * TILE_SIZE });
    }
}

Vector2 TileMap::findSpawnPoint(Vector2 origin) {
    int x = std::ceil(origin.x / TILE_SIZE);
    int y = std::ceil(origin.y / TILE_SIZE);
    for (int i = x; i < std::min(x + 16, TILEMAP_WIDTH); i++) {
        for (int j = y; j < std::min(y + 10, TILEMAP_HEIGHT - 2); j++) {
            if (physics->map[i][j] != PHYSTILE_AIR || physics->map[i][j + 1] != PHYSTILE_AIR || physics->map[i][j + 2] != PHYSTILE_SOLID) {
                continue;
            }
            Vector2 target = Vector2{ (float)(i * TILE_SIZE), (float)(j * TILE_SIZE) };
            if (physics->map[i][j] == PHYSTILE_HALF) {
                target.y += TILE_SIZE / 2;
            }
            return target;
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
    physics->mask = LAYER_PLAYER;
    PhysicsServer::push(physics);

    render = new RenderTileMap();
    RenderingServer::push(render);
}

TileMap::~TileMap() {
    for (const auto& [key, value] : breakables) {
        delete value;
    }

    PhysicsServer::pop(physics);
    delete physics;

    RenderingServer::pop(render);
    delete render;
}
