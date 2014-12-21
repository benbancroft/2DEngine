#include "level.h"

using namespace Core;

namespace Core {
    void Level::Tick(){
        //std::for_each(entities.begin(), entities.end(), [](Entity* entity) { entity->Tick(); });
        //const auto tick = [](Level* level){ level->Tick();};
        std::for_each(entities.begin(), entities.end(), [](Entity* entity) { entity->Tick(); });
        DEBUG_LOG_WRITE_V("Tick", "Ticking base level");
    }

    void Level::Render(Viewport *viewport){

    }
}
