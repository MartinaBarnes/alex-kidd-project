#pragma once
#include "RenderComponent.h"

class ParticleEmitter : public RenderComponent {
    protected:
        const float LIFE_TIME = 2.0f;
        const float VELOCITY_X = 48.0f;
        const float VELOCITY_Y = 256.0f;
    public:
        Vector2 origin;
		Texture2D* texture;
		Rectangle frame;
		bool active;
		float time;
		bool oneShot;

		bool isOnScreen() const override;
		void draw(float) override;
};
