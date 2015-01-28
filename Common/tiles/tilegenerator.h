#ifndef TILEGENERATOR_H
#define TILEGENERATOR_H

#include <iostream>

#include "level.h"
#include "tiles/tilesystem.h"

namespace Core {

    class Level;
    class TileSystem;

    class TileGenerator
    {
        double percentage;
        bool isComplete;
        std::string generationMessage;
        Level* level;
        TileSystem* system;

    public:
        TileGenerator(){
        }

        void SetTileSystem(TileSystem* system){
            this->system = system;
        }

        void StartGenerator(int width, int height);
        void SetLevel(Level* level);
        void SetComplete();
        void SetGenerationMessage(std::string message);

        bool IsComplete();
        virtual void Tick(Engine* engine);
        virtual void Loaded(Engine *engine);
        double GetGenerationPercentage();
        void SetGenerationPercentage(double percentage);
        std::string GetGenerationMessage();

        TileSystem* GetTileSystem(){
            return system;
        }
    };

}

#endif // TILEGENERATOR_H
