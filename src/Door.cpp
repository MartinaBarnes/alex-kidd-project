#include "Door.h"
#include "raylib.h"
#include "PhysicsServer.h"

Door::Door(Vector2 pos, Player* target, bool exit)
{
    player = target;
    aabb.position = pos;
    aabb.size = { 10, 64 };
    isExit = exit;
}

void Door::update(float delta)
{
    player->door = aabb.testAABB(player->physics->aabb) ? this : nullptr;
}
