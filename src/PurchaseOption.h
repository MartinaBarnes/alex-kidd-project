#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Label.h"
#include "PhysicsArea.h"

enum {
    BUY_NONE,
    BUY_LIFE,
    BUY_POGOSTICK
};

/**
 * An item for sale in the shop.
 */
class PurchaseOption : public Entity {
    protected:
        Label* label;
        PhysicsArea* physics;
    public:
        int slot;
        int item = BUY_NONE;
        int price = 0;

        Sprite* sprite;

        void setPrice(int);
        void placeAt(Vector2);
        void onPurchase();
        void update(float) override;

        PurchaseOption();
        ~PurchaseOption();
};
