#pragma once
#include "raylib.h"
#include <vector>
#include <unordered_map>
#include <string>

class ResourceManager {
    private:
        static std::unordered_map<std::string, Texture2D> textures;
        static std::unordered_map<std::string, Sound> sounds;
        static std::string resourceNameFromPath(std::string);
    public:
        static char* resourceDir;
        static char* textureDir;
        static char* soundDir;
        static void loadResources();
        static void unloadResources();
        static Texture2D getTexture(std::string);
        static Sound getSound(std::string);
};
