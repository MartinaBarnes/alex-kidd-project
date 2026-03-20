#include "PhysicsCharacter.h"
#include "PhysicsComponent.h"
#include "PhysicsTileMap.h"
#include "raylib.h"
#include <cmath>
#include <algorithm>

#define TILEMAP_SIZE 128
#define TILE_SIZE 16.0f

bool PhysicsCharacter::isOnScreen(const AABB* viewport) const
{
    return true;
}

bool PhysicsCharacter::testCollision(PhysicsComponent* collider)
{
    if (PhysicsCharacter* character = dynamic_cast<PhysicsCharacter*>(collider)) {
        return aabb.testAABB(character->aabb);
    } else if (PhysicsTileMap* tilemap = dynamic_cast<PhysicsTileMap*>(collider)) {
        int x = std::clamp((int)std::round(aabb.position.x / TILE_SIZE), 0, TILEMAP_SIZE);
        int y = std::clamp((int)std::round(aabb.position.y / TILE_SIZE), 0, TILEMAP_SIZE);
        int x0 = std::clamp((int)std::floor(aabb.position.x / TILE_SIZE), 0, TILEMAP_SIZE);
        int y0 = std::clamp((int)std::floor(aabb.position.y / TILE_SIZE), 0, TILEMAP_SIZE);
        int x1 = std::clamp((int)std::floor((aabb.position.x + aabb.size.x) / TILE_SIZE), 0, TILEMAP_SIZE);
        int y1 = std::clamp((int)std::floor((aabb.position.y + aabb.size.y) / TILE_SIZE), 0, TILEMAP_SIZE);

        onWall = false;
        onGround = false;

        if (tilemap->map[x0][y0]) {
            onWall = aabb.position.x <= x * TILE_SIZE;
            aabb.position.x = std::min(aabb.position.x, x * TILE_SIZE);
            aabb.position.y = std::min(aabb.position.y, y * TILE_SIZE);
            return true;
        } else if (tilemap->map[x1][y0]) {
            onWall = aabb.position.x >= x1 * TILE_SIZE - aabb.size.x;
            aabb.position.x = std::min(aabb.position.x, x1 * TILE_SIZE - aabb.size.x);
            aabb.position.y = std::min(aabb.position.y, y * TILE_SIZE);
            return true;
        } else if (tilemap->map[x0][y1]) {
            onGround = aabb.position.y >= y1 * TILE_SIZE - aabb.size.y;
            aabb.position.x = std::min(aabb.position.x, x * TILE_SIZE);
            aabb.position.y = std::min(aabb.position.y, y1 * TILE_SIZE - aabb.size.y);
            return true;
        } else if (tilemap->map[x1][y1]) {
            onGround = aabb.position.y >= y1 * TILE_SIZE - aabb.size.y;
            aabb.position.x = std::min(aabb.position.x, x1 * TILE_SIZE - aabb.size.x);
            aabb.position.y = std::min(aabb.position.y, y1 * TILE_SIZE - aabb.size.y);
            return true;
        }

        return false;
    }

    return false;
}
