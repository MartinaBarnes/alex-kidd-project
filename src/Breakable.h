#pragma once
#include "ResourceManager.h"
#include "ParticleEmitter.h"
#include "Scene.h"
#include <string>
#include <iostream>

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

        Breakable() = default;
        Breakable(Particles);
        Breakable(Particles, std::string);
};
