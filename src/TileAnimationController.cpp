#include "TileAnimationController.h"

void TileAnimationController::update(float dt) {
    // reset the animation when it's over
    if (frame >= frames.size()) {
        frame = 0;
    }

    // change the tiles to the current frame
    int tile = frames[frame];
    for (int i = 0; i < tiles.size(); i++) {
        Vector2 coords = tiles[i];
        tileMap->render->map[(int)coords.x][(int)coords.y] = tile;
    }

    // run the animation
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
