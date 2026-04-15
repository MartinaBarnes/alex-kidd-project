#include "CameraController.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"

void CameraController::update(float dt) {
    if (mode == CAM_STATIC || player == NULL) {
        wall->enabled = false;
        return;
    }
    switch (mode) {
        case CAM_RIGHT:
            if (player->physics->aabb.position.x - RenderingServer::camera.target.x < 128 || player->physics->velocity.x <= 0.0f) {
                break;
            }
            RenderingServer::camera.target.x += player->physics->velocity.x * dt;
            wall->aabb.position.x = RenderingServer::camera.target.x - wall->aabb.size.x;
            break;
        case CAM_DOWN:
            if (player->physics->aabb.position.y - RenderingServer::camera.target.y < 96 || player->physics->velocity.y <= 0.0f) {
                break;
            }
            RenderingServer::camera.target.y += player->physics->velocity.y * dt;
            break;
    }
    wall->enabled = true;
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
