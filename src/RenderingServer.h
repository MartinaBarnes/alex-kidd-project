#pragma once
#include "RenderComponent.h"
#include <vector>

/**
 * Rendering server class.
 * Handles all of the drawing. Can draw on the world or
 * on the user's camera.
 */
class RenderingServer {
    protected:
        static int cameraFix;
    public:
        static bool visible;
        static Camera2D camera;
        static std::vector<RenderComponent*> components;
        static std::vector<RenderComponent*> overlay;

        static void push(RenderComponent*); // adds a component to the world
        static void pop(RenderComponent*); // removes a component from the world
        static void pushOverlay(RenderComponent*); // adds a component to the camera
        static void popOverlay(RenderComponent*); // removes a component from the camera
        static void update(float);
};
