#include "GameOverLabel.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <string>

void GameOverLabel::draw(float _) {
    std::string texto = "GAME OVER";

    Font font = *ResourceManager::getFont("alex-kidd-in-miracle-world-sms");
    int fontSize = 8;
    int posY = GAME_HEIGHT / 2 - 20;
    int posX;

    int scorePosY = posY + 34;

    // 🔥 POSICIONES SEPARADAS
    int labelX = 28;   // 👉 "SCORE:" más a la izquierda
    int numberX = 88; // 👉 número más a la derecha

    // =========================
    // GAME OVER
    // =========================
    int textWidth = MeasureTextEx(font, texto.c_str(), fontSize, 0).x;
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
