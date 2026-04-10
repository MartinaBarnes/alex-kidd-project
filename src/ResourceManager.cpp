#include "ResourceManager.h"
#include "resource_dir.h"
#include <iostream>

std::unordered_map<std::string, Texture2D> ResourceManager::textures;
std::unordered_map<std::string, Sound> ResourceManager::sounds;

char* ResourceManager::resourceDir = "resources";
char* ResourceManager::textureDir = "textures";
char* ResourceManager::soundDir = "sounds";

std::string ResourceManager::resourceNameFromPath(std::string path) {
    std::string slash = "/";

    #ifdef _WIN32
    slash = "\\";
    #endif

    int min = path.find_last_of(slash) + 1;
    int max = path.find_last_of(".");
    return path.substr(min, max - min);
}

void ResourceManager::loadResources() {
    std::cout << "Loading resources..." << std::endl;

    SearchAndSetResourceDir(ResourceManager::resourceDir);
    FilePathList textureFiles = LoadDirectoryFiles(ResourceManager::textureDir);
    for (int i = 0; i < textureFiles.count; i++) {
        std::string path = textureFiles.paths[i];
        std::string name = ResourceManager::resourceNameFromPath(path);
        std::cout << "Registered texture '" << path << "' as '" << name << "'." << std::endl;
        textures[ResourceManager::resourceNameFromPath(path)] = LoadTexture(path.c_str());
    }
    UnloadDirectoryFiles(textureFiles);

    FilePathList soundFiles = LoadDirectoryFiles(ResourceManager::soundDir);
    for (int i = 0; i < soundFiles.count; i++) {
        std::string path = soundFiles.paths[i];
        std::string name = ResourceManager::resourceNameFromPath(path);
        std::cout << "Registered sound '" << path << "' as '" << name << "'." << std::endl;
        sounds[ResourceManager::resourceNameFromPath(path)] = LoadSound(path.c_str());
    }
    UnloadDirectoryFiles(soundFiles);

    std::cout << "Done loading resources." << std::endl;
}

void ResourceManager::unloadResources() {
    for (auto i = ResourceManager::textures.begin(); i != ResourceManager::textures.end(); i++) {
        UnloadTexture(i->second);
    }
    for (auto i = ResourceManager::sounds.begin(); i != ResourceManager::sounds.end(); i++) {
        UnloadSound(i->second);
    }
}

Texture2D ResourceManager::getTexture(std::string name) {
    return textures[name];
}

Sound ResourceManager::getSound(std::string name) {
    return sounds[name];
}
