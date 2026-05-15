#pragma once
#include "ResourceManager.h"
#include "ParticleEmitter.h"
#include "Scene.h"
#include <string>

/**
 * Breakable tile class
 * Defines the behaviour of a breakable tile type.
 */
class Breakable {
    public:
        Particles particles;
        std::string sound = "break";

        void doBreak(Scene*, Vector2);
        virtual void onBreak(Scene*, Vector2) {};

        Breakable() {};
        Breakable(Particles);
        Breakable(Particles, std::string);
};
