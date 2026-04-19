#pragma once
#include "Entity.h"
#include "PhysicsArea.h"

/**
 * Trigger class
 * An invisible area that activates something upon touching.
 */
class Trigger : public Entity {
    protected:
        PhysicsArea* physics;
    public:
        void update(float) override;

        virtual void onTouch() = 0;

        Trigger(Vector2, Vector2);
        ~Trigger();
};
