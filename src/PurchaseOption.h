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

class PurchaseOption : public Entity {
    protected:
        Sprite* sprite;
        Label* label;
        PhysicsArea* physics;
    public:
        int item = BUY_NONE;
        int price = 0;

        void update(float) override;

        PurchaseOption();
        ~PurchaseOption();
};
