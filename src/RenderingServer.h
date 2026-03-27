#pragma once
#include "RenderComponent.h"
#include <vector>

class RenderingServer {
  public:
    static std::vector<RenderComponent*> components;
    static void push(RenderComponent*);
    static void pop(RenderComponent*);
    static void update(float, const AABB*);
};
