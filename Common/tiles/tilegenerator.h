#ifndef TILEGENERATOR_H
#define TILEGENERATOR_H

#include <iostream>

#include "level.h"

namespace Core {

    class Level;

    class TileGenerator
    {
        double percentage;
        std::string generationMessage;
        Level* level;

    public:
        TileGenerator();

        void StartGenerator(int width, int height);
        void SetLevel(Level* level);

        void Tick();
        void GetGenerationPercentage();
        void GetGenerationMessage();
    };

}

#endif // TILEGENERATOR_H
