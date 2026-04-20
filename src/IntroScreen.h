#pragma once
#include "Entity.h"
#include "Sprite.h"

class IntroScreen : public Entity {
    protected:
        Sprite* sprite;
        float time = 0.0f;
    public:
        void update(float) override;

        IntroScreen();
        ~IntroScreen();
};
