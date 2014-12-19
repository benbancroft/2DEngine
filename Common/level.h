#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <vector>
#include "engine.h"

#include "platform/platform_log.h"

namespace Core
{

    class Engine;

    class Level
    {
        int width = 0;
        int height = 0;
        Engine* engine;
    public:
        Level(int width, int height){
            this->width = width;
            this->height = height;
        }
        void SetEngine(Engine* engine){
            this->engine = engine;
        }
        virtual void Tick(){
            DEBUG_LOG_WRITE_V("Tick", "Ticking base level");
        }
        virtual void Render(){}
    };

    static std::vector <Level*> levels;

}

#endif // LEVEL_H
