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

    auto shadowSelector = [](Core::TileSystem* tileSystem, Maths::Vector2<int> loc) -> int {
        const auto leftBlock = tileSystem->GetBlock(loc.Clone()+Core::TilePosition::Left);
        const auto rightBlock = tileSystem->GetBlock(loc.Clone()+Core::TilePosition::Right);
        const auto topBlock = tileSystem->GetBlock(loc.Clone()+Core::TilePosition::Up);
        const auto bottomBlock = tileSystem->GetBlock(loc.Clone()+Core::TilePosition::Down);
        const auto topLeftBlock = tileSystem->GetBlock(loc.Clone()+Core::TilePosition::Up+Core::TilePosition::Left);
        const auto topRightBlock = tileSystem->GetBlock(loc.Clone()+Core::TilePosition::Up+Core::TilePosition::Right);
        const auto bottomLeftBlock = tileSystem->GetBlock(loc.Clone()+Core::TilePosition::Down+Core::TilePosition::Left);
        const auto bottomRightBlock = tileSystem->GetBlock(loc.Clone()+Core::TilePosition::Down+Core::TilePosition::Right);

        /*if (tileSystem->GetBlock(loc) != 2) return -1;
        else*/ if (topBlock == 1 && leftBlock == 1) return 4;
        else if (topBlock == 1 && rightBlock == 1) return 5;
        else if (bottomBlock == 1 && rightBlock == 1) return 6;
        else if (leftBlock == 1 && rightBlock == 1) return 7;
        else if (topBlock == 1) return 2;
        else if (bottomBlock == 1) return 3;
        else if (leftBlock == 1) return 0;
        else if (rightBlock == 1) return 1;
        else if (topLeftBlock == 1) return 8;
        else if (topRightBlock == 1) return 9;
        else if (bottomRightBlock == 1) return 10;
        else if (bottomLeftBlock == 1) return 11;
        else return -1;
    };

    tileSystem->RegisterBlockType(1, new Core::Block({
        {6, Core::BlockLayer(Core::TilePosition::Centre, { Maths::Vector2<int>(0,7) } )},
        {5, Core::BlockLayer(Core::TilePosition::Up, { Maths::Vector2<int>(0,6) })}
    }));

    /*std::pair<int, Core::BlockLayer > floorLayer = {4, Core::BlockLayer(Core::TilePosition::Centre, {
                           Maths::Vector2<int>(0,0), Maths::Vector2<int>(1,0), Maths::Vector2<int>(2,0), Maths::Vector2<int>(3,0)
                       }, floorSelector)};*/

    tileSystem->RegisterBlockType(2, new Core::Block({
        {8, Core::BlockLayer(Core::TilePosition::Centre, { Maths::Vector2<int>(1,0) } ) },
        {6, Core::BlockLayer(Core::TilePosition::Centre, {
            Maths::Vector2<int>(0,1), Maths::Vector2<int>(1,1), Maths::Vector2<int>(2,1), Maths::Vector2<int>(3,1), Maths::Vector2<int>(4,1), Maths::Vector2<int>(5,1), Maths::Vector2<int>(6,1), Maths::Vector2<int>(7,1), Maths::Vector2<int>(0,2), Maths::Vector2<int>(1,2), Maths::Vector2<int>(2,2), Maths::Vector2<int>(3,2)
        }, shadowSelector)}}));
    //tileSystem->SetBlock(Maths::Vector2<int>(1,1), 1);
    //tileSystem->SetBlock(Maths::Vector2<int>(11,11), 1);
    /*for (int x = 0; x < 10; x++){
        for (int y = 0; y < 20; y++){
            tileSystem->SetBlock(Maths::Vector2<int>(x,y), 1);
        }
    }*/
    tileSystem->Loaded(engine);
    tileSystem->CreateTiles();
    tileSystem->CommitTiles();

    Level::Loaded(engine);
}
