#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "engine.h"
#include "level.h"

namespace Core {

    class Level;
    class Engine;

    class Viewport
    {
        std::vector<Level*> levels;
    public:
        Viewport();
        void Render(Engine* engine);
    };

}

#endif // VIEWPORT_H
