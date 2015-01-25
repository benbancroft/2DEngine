#ifndef TILELAYER_H
#define TILELAYER_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "vector.h"
#include "texture.h"
#include "engine.h"

#include "tilesystem.h"

namespace Core {

    class Render;

    class TileChunk
    {
        std::map<Maths::Vector2<int>, Maths::Vector2<int> > tileMap;
        std::string tilesheetUrl;
        int chunkSize;
        int tileSize;
        GLuint chunkDataTexture;
    public:
        TileChunk(std::string tilesheetUrl, int chunkSize, int tileSize){
            this->tilesheetUrl = tilesheetUrl;
            this->chunkSize = chunkSize;
            this->tileSize = tileSize;
        }

        void Render(Maths::Vector2<int> location, Core::Render* render);

        void AddTile(Maths::Vector2<int> position, Maths::Vector2<int> tile);
        void CommitTiles();
    };

    class TileLayer
    {
        std::string tilesheetUrl;
        std::map<Maths::Vector2<int>, TileChunk*> chunkMap;
        int tileSize;
        int chunkSize;
    public:
        TileLayer(const std::string& tilesheetUrl);
        void SetLayerInfo(int tileSize, int chunkSize){
            this->tileSize = tileSize;
            this->chunkSize = chunkSize;
        }

        void Render(Core::Render* render);

        void CommitTiles();

        void AddTile(Maths::Vector2<int> position, Maths::Vector2<int> tile);

        void ClearTiles();
    };

}

#endif // TILELAYER_H
