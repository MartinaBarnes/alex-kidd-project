#pragma once
#include "raylib.h"
#include "Entity.h"
#include <vector>

class Entity;
class Scene {
  public:
    Color background = BLUE;
    std::vector<Entity*> entities = {};

    void push(Entity*);
    void pop(Entity*);
    void update(float);

    ~Scene();
};
