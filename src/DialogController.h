#include "Entity.h"
#include "DialogBox.cpp"

class DialogController : public Entity {
    protected:
        const float MAX_DELAY = 1.0f;

        DialogBox* welcomeDialog;
        DialogBox* thankYouDialog;
    public:
        float delay = 0.0f;

        void welcome();
        void thankYou();
        void update(float) override;

        DialogController();
        ~DialogController();
};
