#pragma once
#include "Scene.h"

class Scene;
class Entity {
    public:
        bool pausable = false;
        Scene* scene;
        virtual void update(float) {};
};
