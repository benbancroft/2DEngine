#ifndef TILESYSTEM_H
#define TILESYSTEM_H

#include "tilelayer.h"
#include "tilegenerator.h"

namespace Core {

    struct Block{
        Block(std::map<int, Maths::Vector2<int> > blockLayers){
            this->blockLayers = blockLayers;
        }

        std::map<int, Maths::Vector2<int> > blockLayers;
    };

    class TileChunk;

    class TileSystem
    {
        Level* level;
        std::map<Maths::Vector2<int>, TileChunk*> tileChunks;
        std::map<int, Block*> blocks;
        TileGenerator* generator = NULL;

    public:
        int tileSize;
        int chunkSize;
        std::string tilesheetUrl;

        TileSystem(Level* level, TileGenerator* generator, std::string tilesheetUrl, int tileSize, int chunkSize);

        Level* GetLevel(){
            return this->level;
        }

        Block* GetBlockById(int blockId);

        void Tick();
        void Render(Core::Render* render);
        void SetBlock(Maths::Vector2<int> position, int blockId);
        void RegisterBlockType(int blockId, Block* block);

        void CommitTiles();


        void GetGenerationPercentage();
        void GetGenerationMessage();

    };

}

#endif // TILESYSTEM_H
