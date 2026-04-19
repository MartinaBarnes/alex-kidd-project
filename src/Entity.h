#pragma once
#include "Scene.h"

class Scene; // HACK: solves the circular dependency

/**
 * Entity class.
 * Base for all world entities belonging to a Scene.
 */
class Entity {
    public:
        bool markedForDeletion = false; // marks the entity to be safely removed on the next tick
        bool pausable = false; // whether it's updated when the game is paused
        Scene* scene;

        virtual void update(float) {};
        virtual ~Entity() = default;
};
