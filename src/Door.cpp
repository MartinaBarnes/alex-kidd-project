#include "Door.h"
#include "raylib.h"
#include "PhysicsServer.h"

Door::Door(Vector2 pos, Player* player)
{
    this->player = player;
    aabb.position = pos;
    aabb.size = { 32, 64 };
}

void Door::update(float delta)
{
    player->door = aabb.testAABB(player->physics->aabb) ? this : nullptr;
}