#include "mainlevel.h"

void MainLevel::Tick(Core::Engine* engine){
    Level::Tick(engine);
    tileSystem->Tick();
    //DEBUG_LOG_WRITE_V("Tick", "Ticking main level");
}

void MainLevel::Render(Core::Render* render){
    tileSystem->Render(render);
    Level::Render(render);
    //DEBUG_LOG_WRITE_V("Tick", "Ticking main level");
}

void MainLevel::Loaded(Core::Engine *engine){

    const std::string test = "textures/tilesheet";
    mainLayer = tileSystem->AddLayer(new Core::TileLayer(test));
    mainLayer->AddTile(Maths::Vector2<int>(0,0), Maths::Vector2<int>(7,0));
    mainLayer->AddTile(Maths::Vector2<int>(7,7), Maths::Vector2<int>(0,7));
    mainLayer->AddTile(Maths::Vector2<int>(11,11), Maths::Vector2<int>(0,7));

    mainLayer->CommitTiles();
}
