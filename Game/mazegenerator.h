#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <random>
#include "tiles/tilegenerator.h"

class MazeGenerator : public Core::TileGenerator
{
    int group = 0;
    bool connected = false;
    int generateSpeed = 0;
    int corridoorWidth = 3;
    int seed = 100;
    int blockSize = 32;
    int tilesWidth = 20;
    int tilesHeight = 20;

    int startHeight = 0;
    int endHeight = 0;

    Maths::Vector2<double> respawnPoint;

    std::vector<int> groups;
public:
    void Loaded(Core::Engine *engine);
    void Tick(Core::Engine *engine);

    Maths::Vector2<double> GetRespawnPoint(){
        return this->respawnPoint;
    }

    void PopulateMaze(Core::TileSystem *tileSystem, Core::Engine *engine, bool spawnTraps, int currentLevel);

    void RegisterBlocks(Core::Engine *engine);

    bool IsConnected(){
        return connected;
    }
};

#endif // MAZEGENERATOR_H
