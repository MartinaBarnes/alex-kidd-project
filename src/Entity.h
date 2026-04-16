#pragma once
#include "Scene.h"

class Scene;
class Entity {
    public:
        bool pausable;
        Scene* scene;
        virtual void update(float) {};
};
