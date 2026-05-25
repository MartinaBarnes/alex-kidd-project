#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "PhysicsArea.h"
#include "Player.h"

enum {
    ITEM_NONE,
    ITEM_LIFE,
    ITEM_POGOSTICK
};

/**
 * An item for sale in the shop.
 */
class ItemPickup : public Entity {
    protected:
        PhysicsArea* physics;
    public:
        int item = ITEM_NONE;

        Sprite* sprite;

        void placeAt(Vector2);
        void onPickup(Player*);
        void update(float) override;

        ItemPickup();
        ~ItemPickup();
};
