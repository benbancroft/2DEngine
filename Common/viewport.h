#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "render.h"
#include "engine.h"
#include "level.h"

namespace Core {

    class Level;
    class Engine;

    class Viewport
    {
    public:
        Level* level;

        double x = 0.0;
        double y = 0.0;
        int width = 0.0;
        int height = 0.0;

        double levelX = 0.0;
        double levelY = 0.0;
        int levelWidth = 0.0;
        int levelHeight = 0.0;

        Viewport(Level* level, double x, double y, int width, int height, double levelX, double levelY, int levelWidth, int levelHeight);
        void Render(Core::Render* render);

        virtual void OnTouchPress(double x, double y);
        virtual void OnTouchDrag(double x, double y);
    };

}

#endif // VIEWPORT_H
