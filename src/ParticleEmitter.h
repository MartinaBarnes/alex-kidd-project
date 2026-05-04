#pragma once
#include "RenderComponent.h"
#include <vector>

struct Particles {
    Texture2D* texture;
    std::vector<Rectangle> frames;
};

/**
 * Particle emitter class.
 * A basic component that renders the block breaking
 * particles.
 */
class ParticleEmitter : public RenderComponent {
    protected:
        const float LIFE_TIME = 2.0f;
        const float VELOCITY_X = 48.0f;
        const float VELOCITY_Y = 256.0f;
    public:
        Vector2 origin;
        Particles* particles;
		bool active;
		float time;
		bool oneShot; // whether this should be deleted upon finishing

		bool isOnScreen() const override;
		void draw(float) override;
};
