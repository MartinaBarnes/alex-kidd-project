#pragma once
#include "Scene.h"

class Scene;
class Entity {
    public:
        bool markedForDeletion = false;
        bool pausable = false;
        Scene* scene;

        virtual void update(float) {};
        virtual ~Entity() = default;
};
