#include "AABB.h"
#include "raylib.h"
#include <algorithm>

bool AABB::testPoint(const Vector2& point) const
{
    return (point.x >= position.x && point.x < position.x + size.x &&
        point.y >= position.y && point.y < position.y + size.y);
}

bool AABB::testAABB(const AABB& aabb) const
{
    return (position.y < aabb.position.y + aabb.size.y && aabb.position.y < position.y + size.y) &&
           (position.x < aabb.position.x + aabb.size.x && aabb.position.x < position.x + size.x);
}

bool AABB::testCircle(const Vector2& center, float radius) const
{
    int closest_x = std::max(position.x, std::min(center.x, position.x + size.x));
    int closest_y = std::max(position.y, std::min(center.y, position.y + size.y));
    int distance_x = center.x - closest_x;
    int distance_y = center.y - closest_y;
    return (distance_x * distance_x + distance_y * distance_y) <= (radius * radius);
}

AABB::AABB(int x, int y, int w = 16, int h = 16) {
    position.x = x;
    position.y = y;
    size.x = w;
    size.y = h;
}
