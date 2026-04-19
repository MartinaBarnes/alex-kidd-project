#include "Breakable.h"
#include "PhysicsComponent.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "ResourceManager.h"
#include "PhysicsHitbox.h"

void Breakable::update(float _) {
	for (int i = 0; i < physics->colliders.size(); i++) {
		if (PhysicsHitbox* hitbox = dynamic_cast<PhysicsHitbox*>(physics->colliders[i])) {
			doBreak(); // break if we detect a hitbox hitting us
			return;
		}
	}
}

void Breakable::doBreak() {
	onBreak();
	tileMap->physics->map[(int)tileCoords.x][(int)tileCoords.y] = PHYSTILE_AIR;
	tileMap->render->map[(int)tileCoords.x][(int)tileCoords.y] = 0;
	physics->enabled = false;
	particles->active = true;
	PlaySound(*ResourceManager::getSound(sound));
	markedForDeletion = true;
}

Breakable::Breakable(TileMap* map, Vector2 coords) {
	tileMap = map;
	tileCoords = coords;

	physics = new PhysicsArea();
	physics->layer = LAYER_BREAKABLE;
	physics->mask = LAYER_PLAYER;
	physics->aabb.position = Vector2 { tileCoords.x * TILE_SIZE, tileCoords.y * TILE_SIZE };
	physics->aabb.size = Vector2 { TILE_SIZE, TILE_SIZE };
	PhysicsServer::push(physics);

	particles = new ParticleEmitter();
	particles->origin = physics->aabb.position;
	particles->texture = ResourceManager::getTexture("tiles");
	particles->frame = Rectangle { 112, 16, 7, 7 };
	particles->oneShot = true;
	RenderingServer::push(particles);
}

Breakable::Breakable(TileMap* map, Vector2 coords, Texture2D* texture, Rectangle frame) : Breakable(map, coords) {
    particles->texture = texture;
    particles->frame = frame;
}

Breakable::Breakable(TileMap* map, Vector2 coords, char* snd) : Breakable(map, coords) {
    sound = snd;
}

Breakable::Breakable(TileMap* map, Vector2 coords, Texture2D* texture, Rectangle frame, char* snd) : Breakable(map, coords, texture, frame) {
    sound = snd;
}

Breakable::~Breakable() {
	PhysicsServer::pop(physics);
	delete physics;
}
