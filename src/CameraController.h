#include "raylib.h"
#include "Entity.h"
#include "Player.h"

enum CameraMode {
    STATIC,
    DOWN,
    RIGHT,
    ROOM
};

class CameraController : public Entity {
    public:
        CameraMode mode = STATIC;
        Player* player;

        void update(float) override;
};
