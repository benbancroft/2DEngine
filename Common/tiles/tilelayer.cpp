#include "tilelayer.h"

namespace Core {

    /*void TileChunk::Render(Maths::Vector2<int> location, Core::Render *render){

        for (const auto& kv : tileLayers) {
            auto layer = kv.second;
            render->DrawTileChunk(location, tileSystem->tilesheetUrl, tileSystem->tileSize, tileSystem->chunkSize, layer->layerDataTexture, kv.first);
        }
    }*/


    void TileLayer::Render(Core::Render *render){

        render->DrawTileChunk(chunk->location, chunk->tileSystem->tilesheetUrl, chunk->tileSystem->tileSize, chunk->tileSystem->chunkSize, layerDataTexture, depth);
    }

    void TileLayer::addRenderable(){
        chunk->tileSystem->GetLevel()->AddRenderable(this);
    }

    void TileChunk::SetBlock(Maths::Vector2<int> position, int blockId){
        auto block = tileSystem->GetBlockById(blockId);

        if (block == NULL) return;

        auto blockIt = blocks.find(position);
        if (blockIt != blocks.end()) RemoveBlock(position);

        blocks[position] = blockId;

        for (const auto& kv : block->blockLayers) {
            int layerDepth = kv.first;
            auto it = tileLayers.find(layerDepth);
            TileLayer* layer;
            if (it != tileLayers.end()) layer = it->second;
            else{
                layer = new TileLayer(layerDepth, this);
                this->tileLayers[layerDepth] = layer;
            }
            layer->numTiles++;
        }
    }

    void TileChunk::RemoveBlock(Maths::Vector2<int> position){

        auto blockIt = blocks.find(position);
        if (blockIt != blocks.end()){

            int blockId = blockIt->second;

            blocks.erase(position);

            auto block = tileSystem->GetBlockById(blockId);

            for (const auto& kv : block->blockLayers) {
                int layerDepth = kv.first;
                auto it = tileLayers.find(layerDepth);
                if (it != tileLayers.end()){
                    TileLayer* layer = it->second;
                    if (--layer->numTiles <= 0){
                        delete layer;
                        tileLayers.erase(it);
                    }
                }
            }
        }
    }

    void TileChunk::CommitTiles(){
        for (const auto& kv : this->tileLayers) {
            TileLayer* layer = kv.second;

            int chunkSize = tileSystem->chunkSize;
            GLubyte tileMapArray[chunkSize][chunkSize][4];

            for (int h = 0; h < chunkSize; h++){
                for (int w = 0; w < chunkSize; w++){
                    auto it = blocks.find(Maths::Vector2<int>(w,h));

                    Maths::Vector4<unsigned char> tile(0,0,0,0);

                    if (it != blocks.end()){
                        int blockId = it->second;
                        Block* block = tileSystem->GetBlockById(blockId);

                        auto layerIt = block->blockLayers.find(kv.first);
                        if (layerIt != block->blockLayers.end()){
                            Maths::Vector2<int> layerInfo = layerIt->second;
                            tile = Maths::Vector4<unsigned char>(layerInfo.GetX(), layerInfo.GetY(), 255, 0);
                        }
                    }
                    tileMapArray[h][w][0] = tile.GetX();
                    tileMapArray[h][w][1] = tile.GetY();
                    tileMapArray[h][w][2] = tile.GetZ();
                    tileMapArray[h][w][3] = tile.GetW();
                }
            }

            glGenTextures(1, &layer->layerDataTexture);

            glBindTexture(GL_TEXTURE_2D, layer->layerDataTexture);
            //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, chunkSize, chunkSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, tileMapArray);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glBindTexture(GL_TEXTURE_2D, 0);

            DEBUG_LOG_WRITE_V("Tick", "Loaded tile chunk");

        }
    }

}
