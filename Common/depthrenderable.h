#ifndef DEPTHRENDERABLE_H
#define DEPTHRENDERABLE_H

namespace Core {

    class Render;
    class Level;

    class DepthRenderable
    {
    public:
        const int depth;
        DepthRenderable(const int depth) : depth(depth){
        }
        virtual void Render(Core::Render *render){}

    };

}

#endif // DEPTHRENDERABLE_H
