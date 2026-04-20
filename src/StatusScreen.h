#include "RenderComponent.h"

/**
 * Status screen class.
 * Draws the player's current status, such as location, lives,
 * score, money and inventory items.
 */
class StatusScreen : public RenderComponent {
    public:
        int item = 0;

        bool isOnScreen() const override;
        void draw(float) override;
};
