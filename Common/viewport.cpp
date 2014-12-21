#include "viewport.h"

namespace Core {

    Viewport::Viewport()
    {
    }

    void Viewport::Render(Engine* engine){
        std::for_each(levels.begin(), levels.end(), [this](Level* level){ level->Render(this);});
    }

}
