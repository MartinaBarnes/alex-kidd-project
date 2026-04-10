#pragma once
#include "Scene.h"

class Scene;
class Entity {
    public:
        Scene* scene;
        float test = 0.0f;
        virtual void update(float) {};
};
