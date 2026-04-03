#include "PhysicsCharacter.h"
#include "raylib.h"
#include <cmath>
#include <algorithm>


bool PhysicsCharacter::isOnScreen(const AABB* viewport) const
{
    return true;
}

bool PhysicsCharacter::testCollision(float dt, PhysicsComponent* collider)
{
    if (PhysicsCharacter* character = dynamic_cast<PhysicsCharacter*>(collider)) {
        return aabb.testAABB(character->aabb);
    } else if (PhysicsTileMap* tilemap = dynamic_cast<PhysicsTileMap*>(collider)) {
        float tilemap_width = TILEMAP_WIDTH * TILE_SIZE - aabb.size.x;
        aabb.position.x = std::clamp(aabb.position.x + velocity.x * dt, 0.0f, tilemap_width);

        int x0 = std::clamp((int)std::floor(aabb.position.x / TILE_SIZE), 0, TILEMAP_WIDTH);
        int y0 = std::clamp((int)std::floor(aabb.position.y / TILE_SIZE), 0, TILEMAP_HEIGHT);
        int x1 = std::clamp((int)std::floor((aabb.position.x + aabb.size.x - 0.01f) / TILE_SIZE), 0, TILEMAP_WIDTH);
        int y1 = std::clamp((int)std::floor((aabb.position.y + aabb.size.y - 0.01f) / TILE_SIZE), 0, TILEMAP_HEIGHT);

        if (velocity.x < 0.0f) {
            onWall = false;
            if (aabb.position.x <= 0.0f) {
                onWall = true;
            } else {
                for (int i = y0; i <= y1; i++) {
                    if (tilemap->map[x0][i] == TILE_AIR) {
                        continue;
                    }
                    if (x0 < TILEMAP_WIDTH && tilemap->map[x0 + 1][i] == TILE_SOLID) {
                        continue;
                    }
                    float limit = (x0 + 1) * TILE_SIZE;
                    if (aabb.position.x >= limit) {
                        continue;
                    }
                    aabb.position.x = limit;
                    velocity.x = 0.0f;
                    onWall = true;
                    break;
                }
            }
        } else if (velocity.x > 0.0f) {
            onWall = false;
            if (aabb.position.x >= tilemap_width) {
                onWall = true;
            } else {
                for (int i = y0; i <= y1; i++) {
                    if (tilemap->map[x1][i] == TILE_AIR) {
                        continue;
                    }
                    if (x1 > 0 && tilemap->map[x1 - 1][i] == TILE_SOLID) {
                        continue;
                    }
                    float limit = x1 * TILE_SIZE - aabb.size.x;
                    if (aabb.position.x <= limit) {
                        continue;
                    }
                    aabb.position.x = limit;
                    velocity.x = 0.0f;
                    onWall = true;
                    break;
                }
            }
        }

        float tilemap_height = TILEMAP_HEIGHT * TILE_SIZE - aabb.size.y;
        aabb.position.y = std::clamp(aabb.position.y + velocity.y * dt, 0.0f, tilemap_height);

        x0 = std::clamp((int)std::floor(aabb.position.x / TILE_SIZE), 0, TILEMAP_WIDTH);
        y0 = std::clamp((int)std::floor(aabb.position.y / TILE_SIZE), 0, TILEMAP_HEIGHT);
        x1 = std::clamp((int)std::floor((aabb.position.x + aabb.size.x - 0.01f) / TILE_SIZE), 0, TILEMAP_WIDTH);
        y1 = std::clamp((int)std::floor((aabb.position.y + aabb.size.y - 0.01f) / TILE_SIZE), 0, TILEMAP_HEIGHT);

        onGround = false;
        if (velocity.y < 0.0f) {
            if (aabb.position.y <= 0.0f) {
                aabb.position.y = 0.0f;
                velocity.y = 0.0f;
                onCeiling = true;
            } else {
                for (int i = x0; i <= x1; i++) {
                    if (tilemap->map[i][y0] == TILE_AIR) {
                        continue;
                    }
                    if (y0 < TILEMAP_HEIGHT && tilemap->map[i][y0 + 1] == TILE_SOLID) {
                        continue;
                    }
                    float limit = (y0 + 1) * TILE_SIZE;
                    if (aabb.position.y >= limit) {
                        continue;
                    }
                    aabb.position.y = limit;
                    velocity.y = 0.0f;
                    onCeiling = true;
                    break;
                }
            }
        } else if (velocity.y > 0.0f) {
            onCeiling = false;
            if (aabb.position.y + aabb.size.y >= TILEMAP_HEIGHT * TILE_SIZE) {
                aabb.position.y = TILEMAP_HEIGHT * TILE_SIZE - aabb.size.y;
                velocity.y = 0.0f;
                onGround = true;
            } else {
                for (int i = x0; i <= x1; i++) {
                    if (tilemap->map[i][y1] == TILE_AIR) {
                        continue;
                    }
                    if (y1 > 0 && tilemap->map[i][y1 - 1]) {
                        continue;
                    }
                    float limit = y1 * TILE_SIZE - aabb.size.y;
                    if (aabb.position.y <= limit) {
                        continue;
                    }
                    aabb.position.y = limit;
                    velocity.y = 0.0f;
                    onGround = true;
                    break;
                }
            }
        } else {
            int y = std::clamp((int)std::floor((aabb.position.y + aabb.size.y) / TILE_SIZE), 0, TILEMAP_HEIGHT);
            for (int i = x0; i <= x1; i++) {
                if (tilemap->map[i][y] != TILE_AIR) {
                    onGround = true;
                    break;
                }
            }
        }

        return onCeiling || onWall || onGround;
    }

    return false;
}
