#pragma once
#include "Entity.h"
#include "MapPreview.h"
#include "AnimatedSprite.h"

class MapTransitionController : public Entity {
    protected:
        AnimatedSprite* alex;
        float time = 0.0f;
    public:
        float duration = 1.0f;
        float delay = 2.0f;
        bool toLevel2 = false;
        MapPreview* preview;

        void update(float) override;

        MapTransitionController();
        ~MapTransitionController();
};
