#pragma once
#include "Entity.h"
#include "TitleScreenLabel.h"

/**
 * Title screen class.
 * Controller of the title screen scene.
 */
class TitleSplashController : public Entity {
    protected:
        TitleScreenLabel* label;
    public:
        void update(float) override;

        TitleSplashController();
        ~TitleSplashController();
};
