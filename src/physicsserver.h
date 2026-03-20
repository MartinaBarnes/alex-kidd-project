#pragma once
#include "PhysicsComponent.h"
#include "AABB.h"
#include <vector>

class PhysicsServer {
  public:
    static std::vector<PhysicsComponent*> components;
    static void add(PhysicsComponent*);
    static void remove(PhysicsComponent*);
    static void update(const AABB*);
};
