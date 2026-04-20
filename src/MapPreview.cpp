#include "MapPreview.h"
#include "ResourceManager.h"
#include <iostream>

void MapPreview::draw(float dt) {
    int mapSize = 167 * open;
    int edgeSize = 12;

    // draw map
    DrawTexture(*ResourceManager::getTexture("ui_scroll0"), position.x, position.y, WHITE);
    DrawTextureRec(*ResourceManager::getTexture("ui_map0"), Rectangle { 0, 0, mapSize, 134 }, Vector2 { position.x + edgeSize, position.y }, WHITE);
    DrawTexture(*ResourceManager::getTexture("ui_scroll1"), position.x + edgeSize + mapSize, position.y, WHITE);

    if (open < 1.0f) {
        return;
    }

    // run map arrow animation
    if (mapArrowBlinkTime < MAP_ARROW_BLINK_TIME) {
        mapArrowBlinkTime += dt;
    } else {
        mapArrowBlinked = !mapArrowBlinked;
        mapArrowBlinkTime -= MAP_ARROW_BLINK_TIME;
    }

    // draw map arrow
    if (!mapArrowBlinked) {
        DrawTexture(*ResourceManager::getTexture("ui_arrow"), position.x + arrowPosition.x, position.y + arrowPosition.y, WHITE);
    }
}
