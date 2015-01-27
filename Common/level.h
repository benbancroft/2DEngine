#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "engine.h"
#include "viewport.h"
#include "entity.h"
#include "depthrenderable.h"

#include <algorithm>

#include "platform/platform_log.h"

namespace Core
{

    class Engine;
    class Viewport;
    class Entity;
    class DepthRenderable;

    class Level
    {
        //Engine* engine;

        std::vector<Entity*> entities;
        std::vector<DepthRenderable*> renderables;
    public:
        int width = 0;
        int height = 0;
        bool hasBounds = true;

        Level(int width, int height){
            this->width = width;
            this->height = height;
        }
        /*void SetEngine(Engine* engine){
            this->engine = engine;
        }*/

        void AddEntity(Entity* entity, Engine *engine);
        void AddRenderable(DepthRenderable* renderable);

        virtual void Loaded(Engine *engine);
        virtual void Tick(Engine *engine);
        virtual void Render(Core::Render* render);

        virtual void OnTouchPress(double x, double y);
        virtual void OnTouchDrag(double x, double y);
    };

}

#endif // LEVEL_H
