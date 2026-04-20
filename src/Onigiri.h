#include "Entity.h"
#include "PhysicsArea.h"
#include "Sprite.h"

/**
 * Rice ball entity class.
 * A simple entity that transitions to another scene when touched.
 */
class Onigiri : public Entity {
    protected:
        const float DELAY_TIME = 0.5f;

        PhysicsArea* physics;
        Sprite* sprite;
        float delay = 0.0f;
        bool touched = false;
    public:
        void update(float) override;

        Onigiri(Vector2);
        ~Onigiri();
};
