#include "Entity.h"
#include "PhysicsArea.h"
#include "Sprite.h"

class Onigiri : public Entity {
    protected:
        PhysicsArea* physics;
        Sprite* sprite;
    public:
        void update(float) override;

        Onigiri(Vector2);
        ~Onigiri();
};
