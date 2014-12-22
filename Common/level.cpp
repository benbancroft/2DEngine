#include "level.h"

using namespace Core;

namespace Core {
    void Level::Tick(Engine* engine){
        //std::for_each(entities.begin(), entities.end(), [](Entity* entity) { entity->Tick(); });
        //const auto tick = [](Level* level){ level->Tick();};
        std::for_each(entities.begin(), entities.end(), [engine](Entity* entity) { entity->Tick(engine); });
        //DEBUG_LOG_WRITE_V("Tick", "Ticking base level");
    }

    void Level::Loaded(){

    }

    void Level::Render(Core::Render *render){
        std::for_each(entities.begin(), entities.end(), [render](Entity* entity){ entity->Render(render); });
    }
}
