#include "Entity.h"
#include "PhysicsArea.h"
#include "Sprite.h"

/**
 * Rice ball entity class.
 * A simple entity that transitions to another scene when touched.
 */
class Onigiri : public Entity {
    protected:
        PhysicsArea* physics;
        Sprite* sprite;
    public:
        void update(float) override;

        Onigiri(Vector2);
        ~Onigiri();
};
