#pragma once
#include "Scene.h"

class Scene;
class Entity {
    public:
        Scene* scene;
        virtual void update(float) {};
};
