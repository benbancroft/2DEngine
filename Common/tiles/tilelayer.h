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
#include "depthrenderable.h"

namespace Core {

    class Render;
    class TileLayer;
    class TileSystem;

    class TileChunk
    {
        std::map<int, TileLayer*> tileLayers;
        std::map<Maths::Vector2<int>, int> blocks;
        bool hasChanged = false;
    public:
        TileSystem* tileSystem;
        Maths::Vector2<int> location;

        TileChunk(TileSystem* tileSystem, Maths::Vector2<int> location){
            this->tileSystem = tileSystem;
            this->location = location;
        }

        //void Render(Maths::Vector2<int> location, Core::Render* render);

        bool NeedsUpdate(){
            return hasChanged;
        }

        void CreateTiles();
        void CreateTile(int depth, Maths::Vector2<int> position, Maths::Vector2<int> tile);

        void SetBlock(Maths::Vector2<int> position, int blockId);
        int GetBlock(Maths::Vector2<int> position);
        void RemoveBlock(Maths::Vector2<int> position);
        void CommitTiles();

        TileLayer* GetLayer(int depth, bool create = true);
    };

    class TileLayer : public DepthRenderable
    {
        std::map<Maths::Vector2<int>, Maths::Vector2<int> > tileMap;
        void addRenderable();
    public:
        int numTiles;
        GLuint layerDataTexture;
        TileChunk* chunk;

        TileLayer(const int depth, TileChunk* chunk): DepthRenderable(depth){
            this->chunk = chunk;
            addRenderable();
        }

        void Render(Core::Render* render);

        void CreateTile(Maths::Vector2<int> position, Maths::Vector2<int> tile);

        bool GetTile(Maths::Vector2<int> position, Maths::Vector2<int>* output);
    };

}

#endif // TILELAYER_H
