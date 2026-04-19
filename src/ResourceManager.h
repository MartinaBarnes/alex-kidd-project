#pragma once
#include "raylib.h"
#include <vector>
#include <unordered_map>
#include <string>

/**
 * Resource manager class.
 * Static class that loads and stores all media resources
 * of the game, such as textures, sound and music.
 */
class ResourceManager {
    private:
        static std::unordered_map<std::string, Texture2D> textures;
        static std::unordered_map<std::string, Sound> sounds;
        static std::unordered_map<std::string, Music> music;
        static std::string resourceNameFromPath(std::string);
    public:
        static char* resourceDir;
        static char* textureDir;
        static char* soundDir;
        static char* musicDir;
        static void loadResources();
        static void unloadResources();
        static Texture2D* getTexture(std::string);
        static Sound* getSound(std::string);
        static Music* getMusic(std::string);
};
