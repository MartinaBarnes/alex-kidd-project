#include "TileMap.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"

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
