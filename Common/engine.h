#ifndef ENGINE_H
#define ENGINE_H

#include "level.h"
#include "vector.h"
#include <iostream>
#include <algorithm>
#include <map>

#include "asset.h"
#include "asset_utils.h"
#include "texture.h"
#include "platform/platform_gl.h"
#include "platform/platform_log.h"

#include "platform/platform_asset_utils.h"
#include "shader.h"

#include "buffer.h"

namespace Core
{

    class Level;

    class Engine
    {
    private:
        int width;
        int height;

    public:
        Engine();
        void SurfaceCreated();
        void RecreateGLContext();
        void SurfaceChanged(int width, int height);
        void Animate(double currentTime);
        void Render();
        void Tick();

        Maths::Vector2<int> GetResolution();
        Level* RegisterLevel(Level* level);

    };
}

#endif
