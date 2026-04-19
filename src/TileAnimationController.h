#include "Entity.h"
#include "TileMap.h"
#include <vector>

/**
 * Tile animation controller class.
 * Animates a group of tiles from a TileMap.
 */
class TileAnimationController : public Entity {
    protected:
        int frame = 0;
        float next_frame = 0.0f;
    public:
        float frame_rate = 4.0f;
        TileMap* tileMap;
        std::vector<int> frames;
        std::vector<Vector2> tiles = {};

        void update(float) override;

        TileAnimationController(TileMap*, std::vector<int>);
        TileAnimationController(TileMap*, std::vector<int>, std::vector<Vector2>);
};
