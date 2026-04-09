#include "TileMap.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"

/**TileMap::TileMap(map_t const& physmap, tileset_t const& tileset, map_t const& rendermap) {
    physics = new PhysicsTileMap();
    for (int i=0; i<TILEMAP_WIDTH; i++) {
        for (int j=0; j<TILEMAP_HEIGHT; j++) {
            physics->map[i][j] = physmap[i][j];
        }
    }
}*/

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
