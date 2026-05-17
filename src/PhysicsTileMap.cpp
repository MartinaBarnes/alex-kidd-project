#include "PhysicsTileMap.h"
#include "PhysicsComponent.h"
#include "PhysicsHitbox.h"
#include <cmath>
#include <algorithm>

bool PhysicsTileMap::isOnScreen() const
{
    return true;
}

void PhysicsTileMap::resetCollision() {
    PhysicsComponent::resetCollision();
    tilesHit.resize(0);
}

bool PhysicsTileMap::testCollision(float _, PhysicsComponent* component) {
    if (PhysicsHitbox* hitbox = dynamic_cast<PhysicsHitbox*>(component)) {
        int x0 = std::clamp((int)std::floor(hitbox->aabb.position.x / TILE_SIZE), 0, TILEMAP_WIDTH);
        int y0 = std::clamp((int)std::floor(hitbox->aabb.position.y / TILE_SIZE), 0, TILEMAP_HEIGHT);
        int x1 = std::clamp((int)std::floor((hitbox->aabb.position.x + hitbox->aabb.size.x - 0.01f) / TILE_SIZE), 0, TILEMAP_WIDTH);
        int y1 = std::clamp((int)std::floor((hitbox->aabb.position.y + hitbox->aabb.size.y - 0.01f) / TILE_SIZE), 0, TILEMAP_HEIGHT);
        for (int x = x0; x <= x1; x++) {
            for (int y = y0; y <= y1; y++) {
                if (map[x][y] == PHYSTILE_SOLID) {
                    tilesHit.push_back(TileCoords { x, y });
                    if (hitbox->oneShot) {
                        hitbox->enabled = false;
                        return true;
                    }
                }
            }
        }
    }

    return !tilesHit.empty();
}

void PhysicsTileMap::setTileMap(short replacement[TILEMAP_HEIGHT][TILEMAP_WIDTH]) {
    for (int x = 0; x < TILEMAP_WIDTH; x++) {
        for (int y = 0; y < TILEMAP_HEIGHT; y++) {
            map[x][y] = replacement[y][x];
        }
    }
}
