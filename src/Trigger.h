#pragma once
#include "Entity.h"
#include "PhysicsArea.h"

class Trigger : public Entity {
    protected:
        PhysicsArea* physics;
    public:
        void update(float) override;

        virtual void onTouch() = 0;

        Trigger(Vector2, Vector2);
        ~Trigger();
};
