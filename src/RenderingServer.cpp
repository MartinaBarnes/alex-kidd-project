#include "RenderingServer.h"
#include "RenderComponent.h"
#include "raylib.h"

Camera2D RenderingServer::camera = Camera2D { 0 };
std::vector<RenderComponent*> RenderingServer::components = {};
std::vector<RenderComponent*> RenderingServer::overlay = {};

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

void RenderingServer::pushOverlay(RenderComponent* component)
{
    RenderingServer::overlay.push_back(component);
}

void RenderingServer::popOverlay(RenderComponent* component)
{
    int count = RenderingServer::overlay.size();
    for (int i=0; i<count; i++) {
        if (RenderingServer::overlay[i] == component) {
            RenderingServer::overlay[i] = RenderingServer::overlay[count - 1];
            RenderingServer::overlay.pop_back();
            return;
        }
    }
}

void RenderingServer::update(float dt, const AABB* bounds)
{
    BeginMode2D(RenderingServer::camera);
    for (int i=0; i<RenderingServer::components.size(); i++) {
        RenderComponent* component = RenderingServer::components[i];
        component->visible = component->isOnScreen(bounds);
        if (!component->visible) {
            continue;
        }
        component->draw(dt);
    }
    EndMode2D();
};
