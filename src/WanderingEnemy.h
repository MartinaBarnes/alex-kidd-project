#include "Enemy.h"

class WanderingEnemy : public Enemy {
    public:
        float walk_speed;
        int direction = 1;

        void update(float) override;
};
