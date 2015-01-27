#ifndef TILESYSTEM_H
#define TILESYSTEM_H

#include "tilelayer.h"
#include "tilegenerator.h"

namespace Core {

    //enum TilePosition { Centre, Up, Down, Left, Right, DownLeft, DownRight, UpLeft, UpRight };

    namespace TilePosition {

        static const Maths::Vector2<int> Centre(0,0);
        static const Maths::Vector2<int> Up(0,-1);

    }

    struct BlockLayer{
        BlockLayer(Maths::Vector2<int> position, Maths::Vector2<int> tile){
            this->position = position;
            this->tile = tile;
        }

        Maths::Vector2<int> position;
        Maths::Vector2<int> tile;
    };

    struct Block{
        Block(std::map<int, BlockLayer > blockLayers){
            this->blockLayers = blockLayers;
        }

        std::map<int, BlockLayer > blockLayers;
    };

    class TileChunk;
    class TileGenerator;

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

        void Tick(Engine* engine);
        void Loaded(Engine* engine);
        void Render(Core::Render* render);
        void SetBlock(Maths::Vector2<int> position, int blockId);
        int GetBlock(Maths::Vector2<int> position);
        TileChunk* GetChunk(Maths::Vector2<int> chunkPosition, bool create = true);
        void RegisterBlockType(int blockId, Block* block);

        void CommitTiles();

        void CreateTile(int depth, Maths::Vector2<int> position, Maths::Vector2<int> tile, bool createChunk = true);
        void CreateTiles();


        void GetGenerationPercentage();
        void GetGenerationMessage();

    };

}

#endif // TILESYSTEM_H
