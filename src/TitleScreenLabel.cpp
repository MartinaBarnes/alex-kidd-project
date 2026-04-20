#include "TitleScreenLabel.h"
#include "ResourceManager.h"
#include <cmath>

void TitleScreenLabel::draw(float dt) {
    // run animation
    time += dt;

    // 🔥 TEXTURAS
    Texture2D titulo_rojo = *ResourceManager::getTexture("ui_title0");
    Texture2D titulo_verde = *ResourceManager::getTexture("ui_title1");
    Texture2D titulo_amarillo = *ResourceManager::getTexture("ui_title2");
    Texture2D start = *ResourceManager::getTexture("ui_start");

    Texture2D alex1 = *ResourceManager::getTexture("ui_title_img0");
    Texture2D alex2 = *ResourceManager::getTexture("ui_title_img1");
    Texture2D alex3 = *ResourceManager::getTexture("ui_title_img2");
    Texture2D alex4 = *ResourceManager::getTexture("ui_title_img3");
    Texture2D alex5 = *ResourceManager::getTexture("ui_title_img4");

    // =========================
    // 🔴 TÍTULO ROJO
    // =========================
    if (time >= 0.15f && time < 4.0f) {
        DrawTexture(titulo_rojo, TITLE_X, TITLE_Y, WHITE);
    }

    // =========================
    // 🌈 PARPADEO
    // =========================
    if (time >= 4.0f) {

        int frame = (int)std::round(time / BLINK_SPEED) % 3;

        Texture2D tex =
            frame == 0 ? titulo_rojo :
            frame == 1 ? titulo_verde :
            titulo_amarillo;

        DrawTexture(tex, TITLE_X, TITLE_Y, WHITE);
    }

    // =========================
    // 🔥 ALEX
    // =========================
    if (time >= 1.0f) {
        DrawTexture(alex1, ALEX0_X, ALEX0_Y, WHITE);
    }

    if (time >= 1.5f) {
        DrawTexture(alex2, ALEX1_X, ALEX1_Y, WHITE);
    }

    if (time >= 2.0f) {
        DrawTexture(alex3, ALEX2_X, ALEX2_Y, WHITE);
    }

    if (time >= 2.5f) {
        DrawTexture(alex4, ALEX3_X, ALEX3_Y, WHITE);
    }

    if (time >= 3.0f) {
        DrawTexture(alex5, ALEX4_X, ALEX4_Y, WHITE);
    }

    // =========================
    // 🟢 START
    // =========================
    if (time >= 3.5f) {

        DrawTexture(start, START_X, START_Y, WHITE);
    }

}
