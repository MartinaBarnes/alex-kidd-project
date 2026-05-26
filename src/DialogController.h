#include "Entity.h"
#include "DialogBox.cpp"

class DialogController : public Entity {
    protected:
        DialogBox welcomeDialog;
        DialogBox thankYouDialog;
    public:
        void welcome();
        void thankYou();
        void update(float) override;

        DialogController();
        ~DialogController();
};
