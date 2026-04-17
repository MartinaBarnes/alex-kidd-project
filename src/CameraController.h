#include "raylib.h"
#include "Entity.h"
#include "PhysicsSolid.h"
#include "Player.h"

enum {
    CAM_STATIC,
    CAM_DOWN,
    CAM_RIGHT,
    CAM_ROOM
};

class CameraController : public Entity {
    protected:
        PhysicsSolid* wall;
    public:
        int mode = CAM_STATIC;
        Vector2 limits;
        Player* player;

        void update(float) override;

        CameraController();
        ~CameraController();
};
