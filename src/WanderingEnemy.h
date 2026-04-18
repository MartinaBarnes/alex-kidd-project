#include "Enemy.h"

class WanderingEnemy : public Enemy {
    protected:
        float wandered = 0.0f;
    public:
        float walk_speed;
        float wander_distance = 0.0f;
        int direction = 1;

        void update(float) override;
};
