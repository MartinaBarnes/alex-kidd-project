#include "RenderingServer.h"
#include "RenderComponent.h"
#include "raylib.h"
#include <iostream>

std::vector<RenderComponent*> RenderingServer::components = {};

void RenderingServer::push(RenderComponent* component)
{
    RenderingServer::components.push_back(component);
}

void RenderingServer::pop(RenderComponent* component)
{
    int count = RenderingServer::components.size();
    for (int i=0; i<count; i++) {
        if (RenderingServer::components[i] == component) {
            RenderingServer::components[i] = RenderingServer::components[count - 1];
            RenderingServer::components.pop_back();
            return;
        }
    }
}

void RenderingServer::update(float dt, const AABB* bounds)
{
    for (int i=0; i<RenderingServer::components.size(); i++) {
        RenderComponent* component = RenderingServer::components[i];
        component->visible = component->isOnScreen(bounds);
        if (!component->visible) {
            continue;
        }
        component->draw(dt);
    }
};
