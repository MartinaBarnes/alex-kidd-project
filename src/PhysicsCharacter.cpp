#include "PhysicsCharacter.h"
#include "PhysicsSolid.h"
#include "PhysicsTileMap.h"
#include "raylib.h"
#include <cmath>
#include <algorithm>

bool PhysicsCharacter::testCollision(float dt, PhysicsComponent* collider)
{
    // check collision with a solid physics object
    if (PhysicsSolid* solid = dynamic_cast<PhysicsSolid*>(collider)) {
        if (!aabb.testAABB(solid->aabb)) {
            return false;
        }
        if (velocity.x > 0.0f && aabb.position.x + aabb.size.x > solid->aabb.position.x) {
            aabb.position.x = solid->aabb.position.x - aabb.size.x;
        } else if (velocity.x < 0.0f && aabb.position.x < solid->aabb.position.x + solid->aabb.size.x) {
            aabb.position.x = solid->aabb.position.x + solid->aabb.size.x;
        }
        velocity.x = 0.0f;
        // TODO: vertical collisions
        return true;
    }

    // world tiles physics interaction
    if (PhysicsTileMap* tilemap = dynamic_cast<PhysicsTileMap*>(collider)) {
        float tilemap_width = TILEMAP_WIDTH * TILE_SIZE - aabb.size.x;
        aabb.position.x = std::clamp(aabb.position.x + velocity.x * dt, 0.0f, tilemap_width); // avoid going out of bounds

        // get out current tile coordinates based on your position and size
        int x0 = std::clamp((int)std::floor(aabb.position.x / TILE_SIZE), 0, TILEMAP_WIDTH);
        int y0 = std::clamp((int)std::floor(aabb.position.y / TILE_SIZE), 0, TILEMAP_HEIGHT);
        int x1 = std::clamp((int)std::floor((aabb.position.x + aabb.size.x - 0.01f) / TILE_SIZE), 0, TILEMAP_WIDTH);
        int y1 = std::clamp((int)std::floor((aabb.position.y + aabb.size.y - 0.01f) / TILE_SIZE), 0, TILEMAP_HEIGHT);

        inDeathPit = false;
        if (velocity.x < 0.0f) {
            onWall = false;
            if (aabb.position.x <= 0.0f) { // attempted going out of bounds
                onWall = true;
            } else {
                for (int i = y0; i <= y1; i++) {
                    if (tilemap->map[x0][i] == PHYSTILE_AIR) {
                        continue; // do not collide with air
                    }
                    if (tilemap->map[x0][i] == PHYSTILE_DEATHPIT) {
                        inDeathPit = true; // touched a death pit
                        continue;
                    }
                    if (x0 < TILEMAP_WIDTH && tilemap->map[x0 + 1][i] == PHYSTILE_SOLID) {
                        continue; // ignore tiles with an obstructed horizontal face (potentially floor)
                    }
                    float limit = (x0 + 1) * TILE_SIZE;
                    if (aabb.position.x >= limit) {
                        continue; // we haven't collided yet
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
                    if (tilemap->map[x1][i] == PHYSTILE_AIR) {
                        continue; // do not collide with air
                    }
                    if (tilemap->map[x1][i] == PHYSTILE_DEATHPIT) {
                        inDeathPit = true; // touched a death pit
                        continue;
                    }
                    if (x1 > 0 && tilemap->map[x1 - 1][i] == PHYSTILE_SOLID) {
                        continue; // ignore tiles with an obstructed horizontal face (potentially floor)
                    }
                    float limit = x1 * TILE_SIZE - aabb.size.x;
                    if (aabb.position.x <= limit) {
                        continue; // we haven't collided yet
                    }
                    aabb.position.x = limit;
                    velocity.x = 0.0f;
                    onWall = true;
                    break;
                }
            }
        }

        float tilemap_height = TILEMAP_HEIGHT * TILE_SIZE - aabb.size.y;
        aabb.position.y = std::clamp(aabb.position.y + velocity.y * dt, 0.0f, tilemap_height); // avoid going out of bounds

        // reset current tiles since we could've changed our horizontal position when colliding
        x0 = std::clamp((int)std::floor(aabb.position.x / TILE_SIZE), 0, TILEMAP_WIDTH);
        y0 = std::clamp((int)std::floor(aabb.position.y / TILE_SIZE), 0, TILEMAP_HEIGHT);
        x1 = std::clamp((int)std::floor((aabb.position.x + aabb.size.x - 0.01f) / TILE_SIZE), 0, TILEMAP_WIDTH);
        y1 = std::clamp((int)std::floor((aabb.position.y + aabb.size.y - 0.01f) / TILE_SIZE), 0, TILEMAP_HEIGHT);

        onGround = false;
        if (velocity.y < 0.0f) {
            for (int i = x0; i <= x1; i++) {
                if (tilemap->map[i][y0] == PHYSTILE_AIR) {
                    continue; // do not collide with air
                }
                if (tilemap->map[i][y0] == PHYSTILE_DEATHPIT) {
                    inDeathPit = true; // touched a death pit
                    continue;
                }
                if (y0 < TILEMAP_HEIGHT && tilemap->map[i][y0 + 1] == PHYSTILE_SOLID) {
                    continue; // ignore tiles with an obstructed vertical face (avoid getting stuck)
                }
                float limit = (y0 + 1) * TILE_SIZE;
                if (aabb.position.y >= limit) {
                    continue; // we haven't collided yet
                }
                aabb.position.y = limit;
                velocity.y = 0.0f;
                onCeiling = true;
                break;
            }
        } else if (velocity.y > 0.0f) {
            onCeiling = false;
            if (aabb.position.y + aabb.size.y >= TILEMAP_HEIGHT * TILE_SIZE) { // attempted going out of bounds
                aabb.position.y = TILEMAP_HEIGHT * TILE_SIZE - aabb.size.y;
                velocity.y = 0.0f;
                onGround = true;
            } else {
                for (int i = x0; i <= x1; i++) {
                    if (tilemap->map[i][y1] == PHYSTILE_AIR) {
                        continue; // do not collide with air
                    }
                    if (tilemap->map[i][y1] == PHYSTILE_DEATHPIT) {
                        inDeathPit = true; // touched a death pit
                        continue;
                    }
                    if (y1 > 0 && tilemap->map[i][y1 - 1]) {
                        continue; // ignore tiles with an obstructed vertical face (avoid getting stuck)
                    }
                    float limit = y1 * TILE_SIZE - aabb.size.y;
                    if (aabb.position.y <= limit) {
                        continue; // we haven't collided yet
                    }
                    aabb.position.y = limit;
                    velocity.y = 0.0f;
                    onGround = true;
                    break;
                }
            }
        } else {
            // check if we've walked off a platform
            int y = std::clamp((int)std::floor((aabb.position.y + aabb.size.y) / TILE_SIZE), 0, TILEMAP_HEIGHT);
            for (int i = x0; i <= x1; i++) {
                if (tilemap->map[i][y] != PHYSTILE_AIR) {
                    onGround = true;
                    break;
                }
            }
        }

        return onCeiling || onWall || onGround;
    }

    return PhysicsRect::testCollision(dt, collider);
}
