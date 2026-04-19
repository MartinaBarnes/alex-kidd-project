#pragma once
#include "raylib.h"
#include "Entity.h"
#include <vector>

class Entity; // HACK: solves circular dependency

/**
 * Scene class.
 * Contains a level's entities.
 */
class Scene {
    public:
        Color background = BLUE;
        Music* music;
        std::vector<Entity*> entities = {};

        void push(Entity*);
        void pop(Entity*);
        void update(float);

        ~Scene();
};
