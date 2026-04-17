#pragma once
#include "RenderComponent.h"
#include <vector>

class RenderingServer {
  public:
    static bool visible;
    static Camera2D camera;
    static std::vector<RenderComponent*> components;
    static std::vector<RenderComponent*> overlay;

    static void push(RenderComponent*);
    static void pop(RenderComponent*);
    static void pushOverlay(RenderComponent*);
    static void popOverlay(RenderComponent*);
    static void update(float, const AABB*);
};
