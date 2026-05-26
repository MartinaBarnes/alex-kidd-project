#include "RenderComponent.h"

/**
 * Status screen class.
 * Draws the player's current status, such as location, lives,
 * score, money and inventory items.
 */
class StatusScreen : public RenderComponent {
    protected:
        const int FONT_SIZE = 8;
        const int INVENTORY_X = 112;
        const int INVENTORY_Y = 152;
        const int INVENTORY_SLOT_SIZE = 16;
        const float COINS_X = 67.0f;
        const float COINS_Y = 162.0f;
        const float LIVES_X = 35.0f;
        const float LIVES_Y = 178.0f;
        const float SCORE_X = 163.0f;
        const float MAP_ARROW_BLINK_TIME = 0.1f;
        bool mapArrowBlinked = false;
        float mapArrowBlinkTime = 0.0f;
    public:
        const int SLOT_MAX = 6;
        int item = 0;
        bool onLevel2 = false;

        bool isOnScreen() const override;
        void draw(float) override;
};
