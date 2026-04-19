#pragma once
#include "raylib.h"

/**
 * Axis aligned bounding box class.
 * Used for primitive collision detection.
 */
class AABB {
    public:
        Vector2 position;
        Vector2 size;

        bool testPoint(const Vector2&) const;
        bool testAABB(const AABB&) const;
        bool testCircle(const Vector2&, float) const;

        AABB() {};
        AABB(int, int, int, int);
};
