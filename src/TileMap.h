#pragma once
#include "Entity.h"
#include "PhysicsTileMap.h"
#include "RenderTileMap.h"
#include "ParticleEmitter.h"
#include <map>
#include <string>

/**
 * Tile map class.
 * Handles the physics and rendering data of a tile map.
 */
class TileMap : public Entity {
    public:
        static Particles defaultBreakParticles;

        PhysicsTileMap* physics;
        RenderTileMap* render;
        std::map<TileCoords, bool> breakables;
        std::map<int, Particles> breakParticles;
        std::map<int, std::string> breakSounds;

        void update(float) override;

        Vector2 findSpawnPoint(Vector2);
        void setTilePair(int, int, int, int);

        TileMap();
		~TileMap();
};
