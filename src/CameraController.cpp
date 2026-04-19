#include "CameraController.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include <cmath>

void CameraController::update(float dt) {
    // if the camera is static (or we have to valid player) do nothing
    if (mode == CAM_STATIC || !player) {
        wall->enabled = false;
        return;
    }

    // move camera (either right or down) according to mode
    switch (mode) {
        case CAM_RIGHT:
            if (player->physics->aabb.position.x - RenderingServer::camera.target.x < 120.0f || player->physics->velocity.x <= 0.0f) {
                break;
            }
            RenderingServer::camera.target.x += player->physics->velocity.x * dt;
            if (limits.x > 0.0f) {
                RenderingServer::camera.target.x = std::min(RenderingServer::camera.target.x, limits.x);
            }
            wall->aabb.position.x = RenderingServer::camera.target.x - wall->aabb.size.x;
            wall->enabled = true;
            break;
        case CAM_DOWN:
            if (player->physics->aabb.position.y - RenderingServer::camera.target.y < 88.0f || player->physics->velocity.y <= 0.0f) {
                break;
            }
            RenderingServer::camera.target.y += player->physics->velocity.y * dt;
            if (limits.y > 0.0f) {
                RenderingServer::camera.target.y = std::min(RenderingServer::camera.target.y, limits.y);
            }
            wall->enabled = false;
            break;
    }
}

CameraController::CameraController() {
    wall = new PhysicsSolid();
    wall->layer = LAYER_BOUNDS;
    wall->aabb.size.x = 16.0f;
    wall->aabb.size.y = 192.0f;
    wall->aabb.position.x = -wall->aabb.size.x;
    PhysicsServer::push(wall);
}

CameraController::~CameraController() {
    PhysicsServer::pop(wall);
    delete wall;
}
