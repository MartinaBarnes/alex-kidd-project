#pragma once
#include "ResourceManager.h"
#include "ParticleEmitter.h"
#include <string>

/**
 * Breakable tile class
 * Defines the behaviour of a breakable tile type.
 */
class Breakable {
    protected:
        static Particles DEFAULT_BREAK_PARTICLES;
        static std::string DEFAULT_BREAK_SOUND;
    public:
        Particles* particles = &Breakable::DEFAULT_BREAK_PARTICLES;
        std::string sound = Breakable::DEFAULT_BREAK_SOUND;

        void doBreak(Vector2);
        virtual void onBreak(Vector2) {};
};
