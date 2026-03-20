#include "physicscomponent.h"
#include "raylib.h"

class PhysicsTileMap : public PhysicsComponent {
    public:
        bool map[128][128];

        bool isOnScreen(const AABB*) const override;
};
