#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Label.h"
#include "PhysicsArea.h"

enum {
    BUY_LIFE,
    BUY_POGOSTICK
}

class PurchaseOption : public Entity {
    protected:
        Sprite* sprite;
        Label* label;
        PhysicsArea* physics;
    public:
        void update(float) override;

        PurchaseOption();
        ~PurchaseOption();
};
