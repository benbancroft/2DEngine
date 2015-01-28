#include "tilesystem.h"

namespace Core{

    TileSystem::TileSystem(Level* level, TileGenerator* generator, std::string tilesheetUrl, int tileSize, int chunkSize){
        this->level = level;
        this->generator = generator;
        this->tileSize = tileSize;
        this->chunkSize = chunkSize;
        this->tilesheetUrl = tilesheetUrl;

        generator->SetLevel(level);
        generator->SetTileSystem(this);

        //if level has bounds check to see if boundx,y mod chunksize is zero
        //attach generator...
    }

    void TileSystem::Render(Core::Render *render){
        for (const auto& kv : this->tileChunks) {
            //kv.second->Render(kv.first, render);
        }
    }

    void TileSystem::Loaded(Engine* engine){
        if (generator != NULL){
            generator->RegisterBlocks(engine);
            generator->Loaded(engine);
        }
    }

    bool TileSystem::ResolveCollision(Engine* engine, Entity* entity){
    }

    void TileSystem::Tick(Engine* engine){
        if (generator != NULL){
            generator->Tick(engine);
        }
    }

    Block* TileSystem::GetBlockById(int blockId){
        auto it = blocks.find(blockId);

        if (it != blocks.end()){
            return it->second;
        }else
            return NULL;
    }

    TileChunk* TileSystem::GetChunk(Maths::Vector2<int> chunkPosition, bool create){
        auto chunkIter = tileChunks.find(chunkPosition);
        TileChunk* chunk = NULL;
        if (chunkIter != tileChunks.end()) chunk = chunkIter->second;
        else if (create){
            chunk = new TileChunk(this, chunkPosition);
            this->tileChunks[chunkPosition] = chunk;
        }
        return chunk;
    }


    void TileSystem::SetBlock(Maths::Vector2<int> position, int blockId){
        auto chunkPosition = position.Clone()/chunkSize;

        auto chunk = GetChunk(chunkPosition);

        chunk->SetBlock(position%chunkSize, blockId);
    }

    int TileSystem::GetBlock(Maths::Vector2<int> position){
        auto chunkPosition = position.Clone()/chunkSize;

        auto chunk = GetChunk(chunkPosition, false);

        if (chunk != NULL){
            return chunk->GetBlock(position%chunkSize);
        }else{
            return 0;
        }
    }

    void TileSystem::RegisterBlockType(int blockId, Block* block){
        blocks[blockId] = block;
    }

    void TileSystem::CreateTile(int depth, Maths::Vector2<int> position, Maths::Vector2<int> tile, bool createChunk){
        auto chunkPosition = Maths::Vector2<int>(position.GetX(), position.GetY())/chunkSize;
        TileChunk* chunk = GetChunk(chunkPosition, createChunk);
        if (chunk != NULL){
            chunk->CreateTile(depth,position%chunkSize,tile);
        }
    }

    void TileSystem::CreateTiles(){

        for (const auto& kv : tileChunks) {
            TileChunk* chunk = kv.second;
            if (chunk->NeedsUpdate()) chunk->CreateTiles();
        }
    }

    void TileSystem::CommitTiles(){

        for (const auto& kv : tileChunks) {
            TileChunk* chunk = kv.second;
            chunk->CommitTiles();
        }
    }

}
