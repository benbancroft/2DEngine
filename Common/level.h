#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "engine.h"
#include "viewport.h"
#include "entity.h"

#include <algorithm>

#include "platform/platform_log.h"

namespace Core
{

    class Engine;
    class Viewport;
    class Entity;

    class Level
    {
        int width = 0;
        int height = 0;
        //Engine* engine;

        std::vector<Entity*> entities;
    public:
        Level(int width, int height){
            this->width = width;
            this->height = height;
        }
        /*void SetEngine(Engine* engine){
            this->engine = engine;
        }*/

        void AddEntity(Entity* entity, Engine* engine);

        virtual void Loaded(Engine *engine);
        virtual void Tick(Engine *engine);
        void Render(Core::Render* render);
    };

}

#endif // LEVEL_H
