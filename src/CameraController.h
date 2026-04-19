#include "raylib.h"
#include "Entity.h"
#include "PhysicsSolid.h"
#include "Player.h"

// camera controller modes
enum {
    CAM_STATIC,
    CAM_DOWN,
    CAM_RIGHT,
    CAM_ROOM
};

/**
 * Camera controller class.
 * Moves the camera according to player movement, while not letting the player go back.
 */
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
