#ifndef ENTITY_H
#define ENTITY_H

#include "engine.h"
#include "viewport.h"
#include "platform/platform_log.h"

namespace Core
{
    class Engine;
    class Viewport;

    class Entity
    {
    public:
        Entity();

        virtual void Tick(Engine *engine);
        virtual void Render(Core::Render *render);
    };
}

#endif // ENTITY_H
