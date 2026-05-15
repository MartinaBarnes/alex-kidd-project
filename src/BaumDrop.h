#pragma once
#include "Breakable.h"

class BaumDrop : public Breakable {
	public:
	    void onBreak(Scene*, Vector2) override;

		BaumDrop(Particles newParticles) : Breakable(newParticles) {};
};
