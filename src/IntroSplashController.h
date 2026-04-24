#pragma once
#include "Entity.h"
#include "Sprite.h"

class IntroSplashController : public Entity {
    protected:
        Sprite* sprite;
        float time = 0.0f;
    public:
        void update(float) override;

        IntroSplashController();
        ~IntroSplashController();
};
