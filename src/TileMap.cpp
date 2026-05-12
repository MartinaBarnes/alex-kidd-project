#include "TileMap.h"
#include "ParticleEmitter.h"
#include "PhysicsServer.h"
#include "PhysicsTileMap.h"
#include "RenderingServer.h"
#include "ResourceManager.h"
#include <cmath>

Particles TileMap::DEFAULT_BREAK_PARTICLES = Particles{ ResourceManager::getTexture("tiles"), { Rectangle { 112, 16, 7, 7 } } };
std::string TileMap::DEFAULT_BREAK_SOUND = "break";

void TileMap::update(float _) {
    if (!physics) {
        return;
    }
    for (int i = 0; i < physics->tilesHit.size(); i++) {
        TileCoords coords = physics->tilesHit[i];
        if (!breakables[coords]) {
            continue;
        }

        int tile = render->map[coords.x][coords.y];
        setTilePair(coords.x, coords.y, PHYSTILE_AIR, 0);

        ParticleEmitter* emitter = new ParticleEmitter();
        emitter->oneShot = true;

        if (breakParticles.find(tile) != breakParticles.end()) {
            emitter->particles = &breakParticles[tile];
        } else {
            emitter->particles = &DEFAULT_BREAK_PARTICLES;
        }

        if (breakSounds.find(tile) != breakSounds.end()) {
            PlaySound(*ResourceManager::getSound(breakSounds[tile]));
        } else {
            PlaySound(*ResourceManager::getSound(DEFAULT_BREAK_SOUND));
        }

        emitter->active = true;
        RenderingServer::push(emitter);
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
