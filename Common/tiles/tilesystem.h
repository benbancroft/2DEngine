#ifndef TILESYSTEM_H
#define TILESYSTEM_H

#include <functional>

#include "tilelayer.h"
#include "tilegenerator.h"

namespace Core {

    //enum TilePosition { Centre, Up, Down, Left, Right, DownLeft, DownRight, UpLeft, UpRight };

    namespace TilePosition {

        static const Maths::Vector2<int> Centre(0,0);
        static const Maths::Vector2<int> Up(0,-1);
        static const Maths::Vector2<int> Down(0,1);
        static const Maths::Vector2<int> Left(-1,0);
        static const Maths::Vector2<int> Right(1,0);
        static const Maths::Vector2<int> DownLeft(-1,1);
        static const Maths::Vector2<int> DownRight(1,1);
        static const Maths::Vector2<int> UpLeft(-1,-1);
        static const Maths::Vector2<int> UpRight(1,-1);

    }

    struct BlockLayer{
        BlockLayer(Maths::Vector2<int> position, std::vector<Maths::Vector2<int> > tiles, std::function<int(TileSystem*, Maths::Vector2<int>)> predicate = NULL){
            this->position = position;
            this->tiles = tiles;
            this->predicate = predicate;
        }

        Maths::Vector2<int> position;
        std::vector<Maths::Vector2<int> > tiles;
        std::function<int(TileSystem*, Maths::Vector2<int>)> predicate;
    };

    struct Block{
        Block(std::map<int, BlockLayer > blockLayers, bool isSolid){
            this->blockLayers = blockLayers;
            this->isSolid = isSolid;
        }

        bool isSolid;
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

        bool ResolveCollision(Engine* engine, Entity* entity);

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
