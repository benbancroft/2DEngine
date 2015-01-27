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

    std::vector<int> groups;
public:
    void Loaded(Core::Engine *engine);
    void Tick(Core::Engine *engine);
};

#endif // MAZEGENERATOR_H
