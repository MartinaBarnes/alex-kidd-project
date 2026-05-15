#include "BaumDrop.h"
#include "BaumPickup.h"
#include <iostream>

void BaumDrop::onBreak(Scene* scene, Vector2 position) {
	std::cout << "BREAK!!" << std::endl;
	scene->push(new BaumPickup(position, rand() == 0));
}