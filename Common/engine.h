#ifndef ENGINE_H
#define ENGINE_H

#include "level.h"
#include "viewport.h"
#include "vector.h"
#include <iostream>
#include <algorithm>
#include <map>

#include "render.h"

#include "asset.h"
#include "asset_utils.h"
#include "texture.h"
#include "platform/platform_gl.h"
#include "platform/platform_log.h"

#include "platform/platform_asset_utils.h"
#include "shader.h"

namespace Core
{

    class Level;

    class Engine : public Render
    {
    private:
        bool isLoaded = false;
        bool isLoading = false;
        bool beenLoaded = false;
        long unprocessedFrames = 0;
        double lastTime = 0.0;

        std::vector <Level*> levels;
        std::vector <Viewport*> viewports;

        void setLoading(bool state);

    public:
        Engine();
        void SurfaceCreated();
        void RecreateGLContext();
        void SurfaceChanged(int width, int height);
        void Animate(double currentTime);
        virtual void Loaded();
        virtual void Render();
        virtual void Tick();

        virtual void OnTouchPress(double x, double y);
        virtual void OnTouchDrag(double x, double y);

        Level* RegisterLevel(Level* level);
        Viewport* RegisterViewport(Viewport* viewport);

    };
}

#endif
