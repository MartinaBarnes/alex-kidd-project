#pragma once
#include "rendercomponent.h"
#include <vector>

class RenderingServer {
  public:
    static std::vector<RenderComponent*> components;
    static void add(RenderComponent*);
    static void remove(RenderComponent*);
    static void update(const AABB*);
};
