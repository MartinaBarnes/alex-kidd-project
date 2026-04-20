#include "RenderComponent.h"

/**
 * Status screen class.
 * Draws the player's current status, such as location, lives,
 * score, money and inventory items.
 */
class StatusScreen : public RenderComponent {
    protected:
        const int FONT_SIZE = 10;
        const int INVENTORY_X = 112;
        const int INVENTORY_Y = 152;
        const int INVENTORY_SLOT_SIZE = 16;
        const int COINS_X = 67;
        const int COINS_Y = 160;
        const int LIVES_X = 35;
        const int LIVES_Y = 176;
        const int SCORE_X = 163;
        const float MAP_ARROW_BLINK_TIME = 0.1f;
        bool mapArrowBlinked = false;
        float mapArrowBlinkTime = 0.0f;
    public:
        const int SLOT_MAX = 6;
        int item = 0;

        bool isOnScreen() const override;
        void draw(float) override;
};
