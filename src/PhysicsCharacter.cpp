#include "PhysicsCharacter.h"
#include "PhysicsComponent.h"
#include "PhysicsTileMap.h"
#include "raylib.h"
#include <cmath>
#include <algorithm>


bool PhysicsCharacter::isOnScreen(const AABB* viewport) const
{
    return true;
}

bool PhysicsCharacter::testCollision(PhysicsComponent* collider)
{
    aabb.position.x += velocity.x;
    aabb.position.y += velocity.y;

    if (PhysicsCharacter* character = dynamic_cast<PhysicsCharacter*>(collider)) {
        return aabb.testAABB(character->aabb);
    } else if (PhysicsTileMap* tilemap = dynamic_cast<PhysicsTileMap*>(collider)) {
        //onCeiling = false;
        //onWall = false;
        //onGround = false;

        int x0 = std::clamp((int)std::floor(aabb.position.x / TILE_SIZE), 0, TILEMAP_WIDTH);
        int y0 = std::clamp((int)std::floor(aabb.position.y / TILE_SIZE), 0, TILEMAP_HEIGHT);
        int x1 = std::clamp((int)std::floor((aabb.position.x + aabb.size.x) / TILE_SIZE), 0, TILEMAP_WIDTH);
        int y1 = std::clamp((int)std::floor((aabb.position.y + aabb.size.y) / TILE_SIZE), 0, TILEMAP_HEIGHT);

        if (velocity.y > 0.0) {
            onCeiling = false;
            for (int i = x0; i <= x1; i++) {
                if (tilemap->map[i][y1]) {
                    velocity.y = 0.0f;
                    aabb.position.y = std::min(aabb.position.y, (float)y0);
                    onGround = true;
                    break;
                }
            }
        }
        else if (velocity.y < 0.0) {

        }

        // TODO: mirar cuantas casillas ocupa el personaje y calcular colisiones a partir de ahi

        /**if (tilemap->map[x0][y0]) {
            aabb.position.x = std::max(aabb.position.x, x0 * TILE_SIZE);
            aabb.position.y = std::max(aabb.position.y, y0 * TILE_SIZE);
            onCeiling = aabb.position.y <= y0 * TILE_SIZE;
            onWall = aabb.position.x <= x0 * TILE_SIZE;
            return true;
        } else if (tilemap->map[x1][y0]) {
            aabb.position.x = std::min(aabb.position.x, x1 * TILE_SIZE - aabb.size.x);
            aabb.position.y = std::max(aabb.position.y, y0 * TILE_SIZE);
            onCeiling = aabb.position.y <= y0 * TILE_SIZE;
            onWall = aabb.position.x + aabb.size.x >= x1 * TILE_SIZE;
            return true;
        } else if (tilemap->map[x0][y1]) {
            aabb.position.x = std::max(aabb.position.x, x0 * TILE_SIZE);
            aabb.position.y = std::min(aabb.position.y, y1 * TILE_SIZE - aabb.size.y);
            onWall = aabb.position.x <= x0 * TILE_SIZE;
            onGround = aabb.position.y >= y1 * TILE_SIZE - aabb.size.y;
            return true;
        } else if (tilemap->map[x1][y1]) {
            aabb.position.x = std::min(aabb.position.x + aabb.size.x, x1 * TILE_SIZE);
            aabb.position.y = std::min(aabb.position.y + aabb.size.y, y1 * TILE_SIZE);
            onWall = aabb.position.x >= x1 * TILE_SIZE - aabb.size.x;
            onGround = aabb.position.y >= y1 * TILE_SIZE - aabb.size.y;
            return true;
        }*/

        return onCeiling || onWall || onGround;
    }

    return false;
}
