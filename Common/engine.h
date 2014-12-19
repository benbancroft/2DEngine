#ifndef ENGINE_H
#define ENGINE_H

namespace Core
{
    class Engine
    {

    public:
        Engine();
        void SurfaceCreated();
        void RecreateGLContext();
        void SurfaceChanged(int width, int height);
        void Render();
        void Tick();

    };
}

#endif
