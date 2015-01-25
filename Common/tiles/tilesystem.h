#ifndef TILESYSTEM_H
#define TILESYSTEM_H

#include "tilelayer.h"
#include "tilegenerator.h"

namespace Core {

    struct Block{
        Block(std::map<int, Maths::Vector2<int>> blockLayers){
            this->blockLayers = blockLayers;
        }

        std::map<int, Maths::Vector2<int>> blockLayers;
    };

    class TileLayer;

    class TileSystem
    {
        int tileSize;
        int chunkSize;
        Level* level;
        std::vector<TileLayer*> tileLayers;
        std::map<int, Block> blocks;
        TileGenerator* generator = NULL;

    public:
        TileSystem(Level* level, TileGenerator* generator, int tileSize, int chunkSize);

        void Tick();
        void Render(Core::Render* render);
        void AddTile(TileLayer* layer, Maths::Vector2<int> position, Maths::Vector2<int> tile);
        TileLayer *AddLayer(TileLayer* layer);

        void GetGenerationPercentage();
        void GetGenerationMessage();

    };

}

#endif // TILESYSTEM_H
