#include "mainlevel.h"

void MainLevel::Tick(Core::Engine* engine){
    Level::Tick(engine);
    tileSystem->Tick(engine);
    //DEBUG_LOG_WRITE_V("Tick", "Ticking main level");
}

void MainLevel::Render(Core::Render* render){

    tileSystem->Render(render);
    Level::Render(render);
    //DEBUG_LOG_WRITE_V("Tick", "Ticking main level");
}

void MainLevel::Loaded(Core::Engine *engine){

    Level::Loaded(engine);
}
