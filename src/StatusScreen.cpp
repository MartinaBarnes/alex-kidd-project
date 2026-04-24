#include "StatusScreen.h"
#include "ResourceManager.h"
#include "GameState.h"

bool StatusScreen::isOnScreen() const {
    return true;
}

void StatusScreen::draw(float dt) {
    Texture2D arrow = *ResourceManager::getTexture("ui_arrow");

    // run map arrow animation
    if (mapArrowBlinkTime < MAP_ARROW_BLINK_TIME) {
        mapArrowBlinkTime += dt;
    } else {
        mapArrowBlinked = !mapArrowBlinked;
        mapArrowBlinkTime -= MAP_ARROW_BLINK_TIME;
    }

    // draw background
    DrawTexture(*ResourceManager::getTexture("ui_status"), 0, 0, WHITE);

    // draw map arrow
    if (!mapArrowBlinked) {
        DrawTexture(arrow, 172, 72, WHITE);
    }

    // draw item selection
    DrawTexture(arrow, INVENTORY_X + INVENTORY_SLOT_SIZE * item, INVENTORY_Y, WHITE);

    Color yellow = Color { 255, 255, 170, 255 };

    // draw coins
    const char* coins = "0";
    float coinsSize = MeasureText(coins, FONT_SIZE);
    DrawText(coins, COINS_X - coinsSize, COINS_Y, FONT_SIZE, WHITE);

    // draw lives
    std::string livesStr = std::to_string(GameState::lives);
    const char* lives = livesStr.c_str();
    float livesSize = MeasureText(lives, FONT_SIZE);
    DrawText(lives, LIVES_X - livesSize, LIVES_Y, FONT_SIZE, yellow);

    // draw score
    const char* score = "0";
    float scoreSize = MeasureText(score, FONT_SIZE);
    DrawText(score, SCORE_X - scoreSize, LIVES_Y, FONT_SIZE, yellow);
}
