#include "tilelayer.h"

namespace Core {

    TileLayer* TileSystem::AddLayer(TileLayer* layer){
        tileLayers.push_back(layer);
        layer->SetLayerInfo(tileSize, chunkSize);
        return layer;
    }

    void TileLayer::Render(Core::Render *render){

        for (const auto& kv : chunkMap) {
            kv.second->Render(kv.first, render);
        }
    }

    void TileChunk::Render(Maths::Vector2<int> location, Core::Render *render){
        render->DrawTileChunk(location, tilesheetUrl,tileSize, chunkSize, chunkDataTexture);
    }

    void TileSystem::AddTile(TileLayer* layer, Maths::Vector2<int> position, Maths::Vector2<int> tile){
        layer->AddTile(position, tile);
    }

    TileLayer::TileLayer(const std::string &tilesheetUrl)
    {
        this->tilesheetUrl = tilesheetUrl;
    }

    void TileLayer::AddTile(Maths::Vector2<int> position, Maths::Vector2<int> tile){
        auto chunkPosition = Maths::Vector2<int>(position.GetX(), position.GetY())/chunkSize;
        auto chunkIter = chunkMap.find(chunkPosition);
        TileChunk* chunk;
        if (chunkIter != chunkMap.end()) chunk = chunkIter->second;
        else{
            chunk = new TileChunk(tilesheetUrl, chunkSize, tileSize);
            this->chunkMap[chunkPosition] = chunk;
        }
        chunk->AddTile(position%chunkSize, tile);
    }

    void TileChunk::AddTile(Maths::Vector2<int> position, Maths::Vector2<int> tile){
        this->tileMap[position] = tile;
    }

    void TileChunk::CommitTiles(){

        GLubyte tileMapArray[chunkSize][chunkSize][4];

        for (int h = 0; h < chunkSize; h++){
            for (int w = 0; w < chunkSize; w++){
                auto it = tileMap.find(Maths::Vector2<int>(w,h));
                if (it != tileMap.end()){
                    Maths::Vector2<int> tile = it->second;
                    tileMapArray[h][w][0] = (unsigned char)tile.GetX();
                    tileMapArray[h][w][1] = tile.GetY();
                    tileMapArray[h][w][2] = 255;
                }else{
                    tileMapArray[h][w][0] = 0;
                    tileMapArray[h][w][1] = 0;
                    tileMapArray[h][w][2] = 0;
                }
                tileMapArray[h][w][3] = 0;
            }
        }

        glGenTextures(1, &chunkDataTexture);

        glBindTexture(GL_TEXTURE_2D, chunkDataTexture);
        //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, chunkSize, chunkSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, tileMapArray);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);

        DEBUG_LOG_WRITE_V("Tick", "Loaded tile chunk");

    }

    void TileLayer::CommitTiles(){
        for (const auto& kv : chunkMap) {
            kv.second->CommitTiles();
        }
    }

    void TileLayer::ClearTiles(){
        for (const auto& kv : chunkMap) {
            delete kv.second;
        }
        chunkMap.clear();
    }

}
