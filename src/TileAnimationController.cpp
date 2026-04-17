#include "TileAnimationController.h"

void TileAnimationController::update(float dt) {
    if (frame >= frames.size()) {
        frame = 0;
    }
    int tile = frames[frame];
    for (int i = 0; i < tiles.size(); i++) {
        Vector2 coords = tiles[i];
        tileMap->render->map[(int)coords.x][(int)coords.y] = tile + 1;
    }
    next_frame += dt;
	float frame_time = 1.0f / frame_rate;
	if (next_frame >= frame_time) {
		frame++;
		next_frame -= frame_time;
	}
}

TileAnimationController::TileAnimationController(TileMap* map, std::vector<int> anim) {
    tileMap = map;
    frames = anim;
}

TileAnimationController::TileAnimationController(TileMap* map, std::vector<int> anim, std::vector<Vector2> coords) : TileAnimationController(map, anim) {
    tiles = coords;
}
