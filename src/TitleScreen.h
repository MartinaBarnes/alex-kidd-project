#pragma once
#include "Entity.h"
#include "TitleScreenLabel.h"

/**
 * Title screen class.
 * Controller of the title screen scene.
 */
class TitleScreen : public Entity {
    protected:
        TitleScreenLabel* label;
    public:
        void update(float) override;

        TitleScreen();
        ~TitleScreen();
};
