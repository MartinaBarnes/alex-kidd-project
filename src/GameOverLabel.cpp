#include "GameOverLabel.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <string>

void GameOverLabel::draw(float _) {
    std::string texto = "GAME OVER";

    Font font = *ResourceManager::getFont("alex-kidd-in-miracle-world-sms");
    int fontSize = 8;
    float posY = GAME_HEIGHT / 2.0f - 20.0f;
    float posX;

    float scorePosY = posY + 34.0f;

    // 🔥 POSICIONES SEPARADAS
    float labelX = 28.0f;   // 👉 "SCORE:" más a la izquierda
    float numberX = 88.0f; // 👉 número más a la derecha

    // =========================
    // GAME OVER
    // =========================
    float textWidth = MeasureTextEx(font, texto.c_str(), fontSize, 0).x;
    posX = GAME_WIDTH / 2 - textWidth / 2;

    DrawTextEx(font, texto.c_str(), Vector2 { posX, posY }, fontSize, 0, WHITE);

    // =========================
    // SCORE SEPARADO
    // =========================
    std::string label = "SCORE:";
    std::string number = std::to_string(score);

    DrawTextEx(font, label.c_str(), Vector2 { posX - labelX, scorePosY }, fontSize, 0, WHITE);
    DrawTextEx(font, number.c_str(), Vector2 { posX + numberX - MeasureTextEx(font, number.c_str(), fontSize, 0).x, scorePosY }, fontSize, 0, WHITE);

}
