#ifndef ENTITY_H
#define ENTITY_H

#include "platform/platform_log.h"

namespace Core
{
    class Entity
    {
    public:
        //Entity();

        virtual void Tick();
        virtual void Render(){}
    };
}

#endif // ENTITY_H
