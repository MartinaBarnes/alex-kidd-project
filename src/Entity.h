#pragma once
#include "Scene.h"

class Entity {
    public:
        Scene* scene;

        virtual void update(float) {};
};
