#include "tilesystem.h"

namespace Core{

    TileSystem::TileSystem(Level* level, TileGenerator* generator, int tileSize, int chunkSize){
        this->level = level;
        this->generator = generator;
        this->tileSize = tileSize;
        this->chunkSize = chunkSize;

        generator->SetLevel(level);

        //if level has bounds check to see if boundx,y mod chunksize is zero
        //attach generator...
    }

    void TileSystem::Render(Core::Render *render){
        for (const auto& kv : tileLayers) {
            kv->Render(render);
        }
    }

    void TileSystem::Tick(){
        if (generator != NULL){
            generator->Tick();
        }
    }

}
