#pragma once
#include "RenderComponent.h"

/**
 * Title screen label class.
 * Draws the title splash screen.
 */
class TitleScreenLabel : public RenderComponent {
    protected:
        const int TITLE_X = 61;
        const int TITLE_Y = 16;
        const int START_X = 113;
        const int START_Y = 160;
        const int ALEX0_X = 165;
        const int ALEX0_Y = 6;
        const int ALEX1_X = 101;
        const int ALEX1_Y = 118;
        const int ALEX2_X = 8;
        const int ALEX2_Y = 7;
        const int ALEX3_X = 215;
        const int ALEX3_Y = 62;
        const int ALEX4_X = 8;
        const int ALEX4_Y = 71;
        const float BLINK_SPEED = 0.05f;
        float time = 0.0f;
    public:
        void draw(float) override;
};
