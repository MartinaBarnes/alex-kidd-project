#include "BaumDrop.h"
#include "BaumPickup.h"

void BaumDrop::onBreak(Scene* scene, Vector2 position) {
	scene->push(new BaumPickup(position, rand() % 2 == 0, true));
}
