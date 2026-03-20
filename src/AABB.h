#pragma once
#include "raylib.h"

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
