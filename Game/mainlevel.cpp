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

    tileSystem->RegisterBlockType(1, new Core::Block({{8, Maths::Vector2<int>(1,0)}, {6, Maths::Vector2<int>(4,1)}}));
    //tileSystem->SetBlock(Maths::Vector2<int>(1,1), 1);
    //tileSystem->SetBlock(Maths::Vector2<int>(11,11), 1);
    for (int x = 0; x < 10; x++){
        for (int y = 0; y < 20; y++){
            tileSystem->SetBlock(Maths::Vector2<int>(x,y), 1);
        }
    }
    tileSystem->CommitTiles();

    Level::Loaded(engine);
}
