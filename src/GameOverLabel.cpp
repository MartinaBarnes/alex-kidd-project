#include "GameOverLabel.h"
#include <SceneManager.h>
#include <string>

void GameOverLabel::draw(float _) {
    std::string texto = "GAME OVER";

    int fontSize = 10;
    int posY = GAME_HEIGHT / 2 - 22;
    int posX;

    int scorePosY = posY + 32;

    // 🔥 POSICIONES SEPARADAS
    int labelX = 28;   // 👉 "SCORE:" más a la izquierda
    int numberX = 90; // 👉 número más a la derecha

    // =========================
    // GAME OVER
    // =========================
    int textWidth = MeasureText(texto.c_str(), fontSize);
    posX = GAME_WIDTH / 2 - textWidth / 2;

    DrawText(texto.c_str(), posX, posY, fontSize, WHITE);

    // =========================
    // SCORE SEPARADO
    // =========================
    std::string label = "SCORE:";
    std::string number = std::to_string(score);

    DrawText(label.c_str(), posX - labelX, scorePosY, fontSize, WHITE);
    DrawText(number.c_str(), posX + numberX, scorePosY, fontSize, WHITE);

}
