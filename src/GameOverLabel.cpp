#include "GameOverLabel.h"
#include <SceneManager.h>
#include <string>
#include <iostream>

bool GameOverLabel::isOnScreen() const {
    return true;
}

void GameOverLabel::draw(float _) {
    std::string texto = "GAME OVER";

    int fontSize = 16;
    int posY = GAME_HEIGHT / 2 - 10;
    int posX;

    int scoreFontSize = 8;
    int scorePosY = posY + 18;

    // 🔥 POSICIONES SEPARADAS
    int labelX = 0;   // 👉 "SCORE:" más a la izquierda
    int numberX = 64; // 👉 número más a la derecha

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

    DrawText(label.c_str(), posX - labelX, scorePosY, scoreFontSize, WHITE);
    DrawText(number.c_str(), posX + numberX, scorePosY, scoreFontSize, WHITE);

}