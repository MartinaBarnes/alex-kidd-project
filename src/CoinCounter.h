#pragma once
#include "Entity.h"
#include "Label.h"

class CoinCounter : public Entity {
    protected:
        Label* label;
    public:
        void update(float) override;

        CoinCounter();
        CoinCounter(Vector2);
        ~CoinCounter();
};
