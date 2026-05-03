#pragma once
#include "PhysicsArea.h"

/**
 * Physics hitbox class.
 * A non-solid physics object for hitboxes.
 */
class PhysicsHitbox : public PhysicsArea {
    public:
        bool oneShot; // whether this hitbox only hits once per frame
};
