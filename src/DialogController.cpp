#include "DialogController.h"
#include "RenderingServer.h"
#include "ResourceManager.h"
#include "SceneManager.h"

void DialogController::welcome() {
    SceneManager::pause = true;
    welcomeDialog->start();
}

void DialogController::thankYou() {
    SceneManager::pause = true;
    thankYouDialog->start();
}

void DialogController::update(float dt) {
    if (!SceneManager::pause) {
        return;
    }
    if (welcomeDialog->IsDone() || thankYouDialog->IsDone()) {
        if (delay < MAX_DELAY) {
            delay += dt;
            return;
        }
        welcomeDialog->reset();
        thankYouDialog->reset();
        SceneManager::pause = false;
        delay = 0.0f;
    }
}

DialogController::DialogController() {
    Font font = *ResourceManager::getFont("alex-kidd-in-miracle-world-sms");

    welcomeDialog = new DialogBox(
        { 32, 32, 218, 42 },
        { "Welcome! Please buy", "the things that you like." },
        font
    );
    welcomeDialog->pausable = true;
    RenderingServer::pushOverlay(welcomeDialog);

    thankYouDialog = new DialogBox(
        { 32, 32, 92, 22 },
        { "Thank you." },
        font
    );
    thankYouDialog->pausable = true;
    RenderingServer::pushOverlay(thankYouDialog);
}

DialogController::~DialogController() {
    RenderingServer::popOverlay(welcomeDialog);
    delete welcomeDialog;

    RenderingServer::popOverlay(thankYouDialog);
    delete thankYouDialog;
}
