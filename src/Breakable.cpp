#include "Breakable.h"
#include "PhysicsArea.h"
#include "PhysicsServer.h"

void Breakable::update(float _) {
	for (int i = 0; i < physics->colliders.size(); i++) {
		if (PhysicsArea* hitbox = dynamic_cast<PhysicsArea*>(physics->colliders[i])) {
			doBreak();
			return;
		}
	}
}

void Breakable::doBreak() {
	onBreak();
	tileMap->physics->map[(int)tileCoords.x][(int)tileCoords.y] = PHYSTILE_AIR;
	tileMap->render->map[(int)tileCoords.x][(int)tileCoords.y] = 0;
	scene->pop(this);
	delete this;
}

Breakable::Breakable(TileMap* tileMap, Vector2 tileCoords) {
	this->tileMap = tileMap;
	this->tileCoords = tileCoords;
	physics = new PhysicsArea();
	physics->layer = LAYER_BREAKABLE;
	physics->mask = LAYER_PLAYER;
	physics->aabb.position = Vector2 { tileCoords.x * TILE_SIZE, tileCoords.y * TILE_SIZE };
	physics->aabb.size = Vector2 { TILE_SIZE, TILE_SIZE };
	PhysicsServer::push(physics);
}

Breakable::~Breakable() {
	PhysicsServer::pop(physics);
	delete physics;
}