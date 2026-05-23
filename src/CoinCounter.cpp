#include "CoinCounter.h"
#include "RenderingServer.h"
#include "GameState.h"

void CoinCounter::update(float _) {
    label->text = std::to_string(GameState::baums);
}

CoinCounter::CoinCounter() {
    label = new Label();
    label->align = TEXTALIGN_RIGHT;
    RenderingServer::push(label);
}

CoinCounter::CoinCounter(Vector2 position) : CoinCounter() {
    label->position = position;
}

CoinCounter::~CoinCounter() {
    RenderingServer::pop(label);
    delete label;
}
