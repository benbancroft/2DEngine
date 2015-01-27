#include "tilesystem.h"

namespace Core{

    TileSystem::TileSystem(Level* level, TileGenerator* generator, std::string tilesheetUrl, int tileSize, int chunkSize){
        this->level = level;
        this->generator = generator;
        this->tileSize = tileSize;
        this->chunkSize = chunkSize;
        this->tilesheetUrl = tilesheetUrl;

        generator->SetLevel(level);

        //if level has bounds check to see if boundx,y mod chunksize is zero
        //attach generator...
    }

    void TileSystem::Render(Core::Render *render){
        for (const auto& kv : this->tileChunks) {
            //kv.second->Render(kv.first, render);
        }
    }

    void TileSystem::Tick(){
        if (generator != NULL){
            generator->Tick();
        }
    }

    Block* TileSystem::GetBlockById(int blockId){
        auto it = blocks.find(blockId);

        if (it != blocks.end()){
            return it->second;
        }else
            return NULL;
    }


    void TileSystem::SetBlock(Maths::Vector2<int> position, int blockId){
        auto chunkPosition = Maths::Vector2<int>(position.GetX(), position.GetY())/chunkSize;
        auto chunkIter = tileChunks.find(chunkPosition);
        TileChunk* chunk;
        if (chunkIter != tileChunks.end()) chunk = chunkIter->second;
        else{
            chunk = new TileChunk(this, chunkPosition);
            this->tileChunks[chunkPosition] = chunk;
        }
        chunk->SetBlock(position%chunkSize, blockId);
    }

    void TileSystem::RegisterBlockType(int blockId, Block* block){
        blocks[blockId] = block;
    }

    void TileSystem::CommitTiles(){

        for (const auto& kv : tileChunks) {
            TileChunk* chunk = kv.second;
            chunk->CommitTiles();
        }
    }

}
