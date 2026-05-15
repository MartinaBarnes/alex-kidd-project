#include "BaumPickup.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "ResourceManager.h"
#include "GameState.h"

void BaumPickup::update(float dt) {
	for (int i = 0; i < physics->colliders.size(); i++) {
		PlaySound(*ResourceManager::getSound("coin_pickup"));
		GameState::baums += baums;
		markedForDeletion = true;
		return;
	}
	if (!temp) {
	    return;
	}
	time += dt;
	if (time >= DISAPPEAR_TIME) {
	    markedForDeletion = true;
	}
}

BaumPickup::BaumPickup(Vector2 position, bool large, bool disappear) {
	baums = large ? LARGE_BAUM_COUNT : SMALL_BAUM_COUNT;
	temp = disappear;

	physics = new PhysicsArea();
	physics->aabb = AABB { (int)position.x, (int)position.y, 16, 16 };
	physics->mask = LAYER_PLAYER;
	PhysicsServer::push(physics);

	sprite = new Sprite();
	sprite->position = position;
	sprite->texture = ResourceManager::getTexture("items");
	sprite->frame = Rectangle { large ? 32.0f : 16.0f, 0.0f, 16.0f, 16.0f };
	RenderingServer::push(sprite);
}

BaumPickup::~BaumPickup() {
	PhysicsServer::pop(physics);
	delete physics;

	RenderingServer::pop(sprite);
	delete sprite;
}
