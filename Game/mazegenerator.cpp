#include "mazegenerator.h"

int get2DIndex(int x, int y, int width){
    return x*width+y;
}

void MazeGenerator::RegisterBlocks(Core::Engine* engine){

    Core::TileSystem* tileSystem = GetTileSystem();

    //shadow tile selector

    auto shadowSelector = [](Core::TileSystem* tileSystem, Maths::Vector2<int> loc) -> int {
        //auto loc = test.Clone();
        const auto leftBlock = tileSystem->GetBlock(loc+Core::TilePosition::Left);
        const auto rightBlock = tileSystem->GetBlock(loc+Core::TilePosition::Right);
        const auto topBlock = tileSystem->GetBlock(loc+Core::TilePosition::Up);
        const auto bottomBlock = tileSystem->GetBlock(loc+Core::TilePosition::Down);
        const auto topLeftBlock = tileSystem->GetBlock(loc+Core::TilePosition::Up+Core::TilePosition::Left);
        const auto topRightBlock = tileSystem->GetBlock(loc+Core::TilePosition::Up+Core::TilePosition::Right);
        const auto bottomLeftBlock = tileSystem->GetBlock(loc+Core::TilePosition::Down+Core::TilePosition::Left);
        const auto bottomRightBlock = tileSystem->GetBlock(loc+Core::TilePosition::Down+Core::TilePosition::Right);

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

    //floor tile randomiser

    auto floorTileSelector = [engine](Core::TileSystem* tileSystem, Maths::Vector2<int> loc){
        return engine->RandomInteger(0, 3);
    };

    std::pair<int, Core::BlockLayer > wallBaseInfo = {6, Core::BlockLayer(Core::TilePosition::Centre, { Maths::Vector2<int>(0,7) } )};
    std::pair<int, Core::BlockLayer > wallTopInfo = {5, Core::BlockLayer(Core::TilePosition::Up, { Maths::Vector2<int>(0,6) })};

    //register base wall block

    tileSystem->RegisterBlockType(1, new Core::Block({wallBaseInfo, wallTopInfo}, true));

    //register dart trap block

    tileSystem->RegisterBlockType(5, new Core::Block({wallBaseInfo, wallTopInfo,
        {4, Core::BlockLayer(Core::TilePosition::Centre, { Maths::Vector2<int>(2,7) })}
    }, true));

    //register floor block

    std::pair<int, Core::BlockLayer > floorLayer = {8, Core::BlockLayer(Core::TilePosition::Centre, {
                           Maths::Vector2<int>(0,0), Maths::Vector2<int>(1,0), Maths::Vector2<int>(2,0), Maths::Vector2<int>(3,0)
                       }, floorTileSelector)};

    tileSystem->RegisterBlockType(2, new Core::Block({
        floorLayer,
        {7, Core::BlockLayer(Core::TilePosition::Centre, {
            Maths::Vector2<int>(0,1), Maths::Vector2<int>(1,1), Maths::Vector2<int>(2,1), Maths::Vector2<int>(3,1), Maths::Vector2<int>(4,1), Maths::Vector2<int>(5,1), Maths::Vector2<int>(6,1), Maths::Vector2<int>(7,1), Maths::Vector2<int>(0,2), Maths::Vector2<int>(1,2), Maths::Vector2<int>(2,2), Maths::Vector2<int>(3,2)
        }, shadowSelector)}}, false));

    //register maze entrance

    tileSystem->RegisterBlockType(3, new Core::Block({floorLayer,
        {7, Core::BlockLayer(Core::TilePosition::Centre, { Maths::Vector2<int>(5,0) })}
    }, true));

    //register maze exit

    tileSystem->RegisterBlockType(4, new Core::Block({
        {7, Core::BlockLayer(Core::TilePosition::Centre, { Maths::Vector2<int>(4,0) })}
    }, false));

    //register spike trap

    tileSystem->RegisterBlockType(6, new Core::Block({floorLayer,
        {7, Core::BlockLayer(Core::TilePosition::Centre, { Maths::Vector2<int>(6,0) })}
    }, false));

    //register chest block

    tileSystem->RegisterBlockType(7, new Core::Block({
        floorLayer,
        {7, Core::BlockLayer(Core::TilePosition::Centre, {
            Maths::Vector2<int>(3,7)
        })},
        {4, Core::BlockLayer(Core::TilePosition::Up, {
            Maths::Vector2<int>(3,6)
        })}}, true));
}

void MazeGenerator::PopulateMaze(Core::TileSystem* tileSystem, Core::Engine* engine, bool spawnTraps, int currentLevel){

    int intersections = 10 + (currentLevel-1)*2;;

    if (spawnTraps){

        //Spawn traps

        for (int i = 0; i < 4 + (currentLevel-1)*3; i++){

            int rx = 0;
            int ry = 0;

            int fitsCriteria = false;

            do
            {
                rx = engine->RandomInteger(1, tilesWidth);
                ry = engine->RandomInteger(1, tilesHeight);

                if (tileSystem->GetBlock(Maths::Vector2<int>(rx, ry)) == 1 && tileSystem->GetBlock(Maths::Vector2<int>(rx, ry+1)) == 2 && tileSystem->GetBlock(Maths::Vector2<int>(rx, ry+4)) == 1) fitsCriteria = true;

            } while(!fitsCriteria);

            tileSystem->SetBlock(Maths::Vector2<int>(rx, ry), 5);
        }

        for (int i = 0; i < 4 + (currentLevel-1)*3; i++){

            int rx = 0;
            int ry = 0;

            int fitsCriteria = false;

            do
            {
                rx = engine->RandomInteger(1, tilesWidth);
                ry = engine->RandomInteger(1, tilesHeight);

                if (tileSystem->GetBlock(Maths::Vector2<int>(rx, ry)) == 2) fitsCriteria = true;

            } while(!fitsCriteria);

            tileSystem->SetBlock(Maths::Vector2<int>(rx, ry), 6);
        }

        //Spawn chests

        std::vector<Maths::Vector2<int> > deadEnds;

        for (int dx = 0; dx < intersections; dx++){
            for (int dy = 0; dy < intersections; dy++){
                int ix = 1+dx*(corridoorWidth+1);
                int iy = 1+dy*(corridoorWidth+1);

                int sidesBlocked = 0;
                if (tileSystem->GetBlock(Maths::Vector2<int>(ix-1, iy)) == 1) sidesBlocked++;
                if (tileSystem->GetBlock(Maths::Vector2<int>(ix, iy-1)) == 1) sidesBlocked++;
                if (tileSystem->GetBlock(Maths::Vector2<int>(ix+3, iy)) == 1) sidesBlocked++;
                if (tileSystem->GetBlock(Maths::Vector2<int>(ix, iy+3)) == 1) sidesBlocked++;

                if (sidesBlocked == 3 && tileSystem->GetBlock(Maths::Vector2<int>(ix, iy-1)) == 1){
                    deadEnds.push_back(Maths::Vector2<int>(ix+1,iy));
                }
            }
        }

        int numChests = floor(deadEnds.size()*0.35);

        for (int i = 0; i < numChests; i++){
            int position = engine->RandomInteger(0, deadEnds.size()-1);

            Maths::Vector2<int> location = deadEnds[position];

            //check if exists?

            tileSystem->SetBlock(location, 7);

            deadEnds.erase(deadEnds.begin() + position);
        }

        /*for (int i = 0; i < 20; i++){

            int rx = 0;
            int ry = 0;

            int fitsCriteria = false;

            do
            {
                rx = 1+irandom(global.width-1);
                ry = 1+irandom(global.height-1);

                if (get_block_at(rx, ry) == 0 && get_block_at(rx, ry-1) == 1) fitsCriteria = true;

            } until(fitsCriteria == true);

            global.blocks[rx, ry] = 7;
        }*/

        //commit_tiles_to_room(global.wallUpperDepth, global.wallLowerDepth, global.bombUpperDepth, global.bombDepth, global.floorDepth, global.chestDepth);
    }

    //Spawn enemies

    /*int numMonsters = floor(0.1*global.intersections*global.intersections);

    for (int i = 0; i < numMonsters; i++){
        int rx = 0;
        int ry = 0;

        int hasLOS = false;

        do
        {
            rx = 1+irandom((global.width)/(global.corridoor_width+1)-1)*(global.corridoor_width+1);
            ry = 1+irandom((global.height)/(global.corridoor_width+1)-1)*(global.corridoor_width+1);

                int returnData = has_line_of_sight_tiles(rx, ry, 1, global.startHeight, false);
                hasLOS = returnData[0];
        }
        until ((hasLOS == false && distance_between_points(rx, ry, 1, global.startHeight) > global.view_distance) || global.inLevel == false)

        int monster = irandom(1);
        switch (monster){
            case 0:
                instance_create(rx*global.block_size, ry*global.block_size, bat);
                break;
            case 1:
                instance_create(rx*global.block_size, ry*global.block_size, spider);
                break;
        }
    }

    //Spawn pickups

    for (int i = 0; i < 2+(currentLevel-1); i++){
        rx = 1+irandom((global.width)/(global.corridoor_width+1)-1)*(global.corridoor_width+1);
        ry = 1+irandom((global.height)/(global.corridoor_width+1)-1)*(global.corridoor_width+1);

        instance_create(rx*global.block_size, ry*global.block_size, health_pickup);
    }*/
}

void MazeGenerator::Loaded(Core::Engine* engine){

    Core::TileSystem* tileSystem = GetTileSystem();

    tilesWidth -= (tilesWidth % (corridoorWidth+1))-1;
    tilesHeight -= (tilesHeight % (corridoorWidth+1))-1;

    startHeight = 2+engine->RandomInteger(0, (tilesHeight)/(corridoorWidth+1)-1)*(corridoorWidth+1);
    endHeight = 2+engine->RandomInteger(0, (tilesHeight)/(corridoorWidth+1)-1)*(corridoorWidth+1);

    generateSpeed = ceil(sqrt(tilesWidth*tilesHeight)*0.1);

    //blocks = new List<int>(get2DIndex(tilesWidth, tilesHeight, tilesWidth));
    groups = std::vector<int>(get2DIndex(tilesWidth/(corridoorWidth+1), tilesHeight/(corridoorWidth+1), tilesWidth/(corridoorWidth+1)));

    group = 0;

    //Create solid maze
    for (int ix=0; ix<tilesWidth; ix++) {
        for (int iy=0; iy<tilesHeight; iy++) {
            tileSystem->SetBlock(Maths::Vector2<int>(ix, iy), 1);
        }
    }

    //Give structure
    for (int ix=0; ix<tilesWidth; ix++) {
        for (int iy=0; iy<tilesHeight; iy++) {
            int blockId = tileSystem->GetBlock(Maths::Vector2<int>(ix, iy));
            if (blockId != 1) {
                //global.blocks[ix, iy] = 1;
            }
            else if (ix % (corridoorWidth+1) == 1 && iy % (corridoorWidth+1) == 1 && ix > 0 && ix < tilesWidth-1 && iy > 0 && iy < tilesHeight-1) {
                groups[get2DIndex(ix/(corridoorWidth+1), iy/(corridoorWidth+1), tilesWidth/(corridoorWidth+1))] = group++;
                for (int i = 0; i < corridoorWidth; i++) {
                    for (int j = 0; j < corridoorWidth; j++) {
                        tileSystem->SetBlock(Maths::Vector2<int>(ix+i, iy+j), /*-2*/ 2);
                    }
                }
                tileSystem->SetBlock(Maths::Vector2<int>(ix, iy), /*-1*/ 2);

                //ds_list_insert(intersections, 0, pos);

                //show_debug_message("DB: " + string(ix/2) + " and " + string(iy/2));
                //instance_create(ix*32,iy*32, example_block);
            }else{
                tileSystem->SetBlock(Maths::Vector2<int>(ix, iy), 1);
            }
        }
    }

    //Spawn entrance and exit

    tileSystem->SetBlock(Maths::Vector2<int>(1, startHeight), 3);
    tileSystem->SetBlock(Maths::Vector2<int>(tilesWidth-2, endHeight), 4);
}

void MazeGenerator::Tick(Core::Engine* engine){
    if (connected == false) {

        Core::TileSystem* tileSystem = GetTileSystem();

        engine->SetSeed(seed);

        int groupWidth = tilesWidth/(corridoorWidth+1);

        for (int r=0; r<generateSpeed; r++) {
            /*int rx = engine->RandomInteger(0, ((tilesWidth/(corridoorWidth+1)-1)*(corridoorWidth+1)).toInt());
               int ry = engine->RandomInteger(1, ((tilesHeight/(corridoorWidth+1)-1)*(corridoorWidth+1)).toInt());*/

            int rx = 1+engine->RandomInteger(0, (tilesWidth)/(corridoorWidth+1)-1)*(corridoorWidth+1);
            int ry = 1+engine->RandomInteger(0, (tilesHeight)/(corridoorWidth+1)-1)*(corridoorWidth+1);

            int dir = engine->RandomInteger(0, 3);

            int dx = 0;
            int dy = 0;

            if (dir == 0) {
                dx = 1;
                dy = 0;
            }else if (dir == 1) {
                dx = -1;
                dy = 0;
            }else if (dir == 2) {
                dx = 0;
                dy = 1;
            }else if (dir == 3) {
                dx = 0;
                dy = -1;
            }

            int destx = rx + (corridoorWidth+1)*dx;
            int desty = ry + (corridoorWidth+1)*dy;

            if (destx <= 0 || destx >= tilesWidth-1 || desty <= 0 || desty >= tilesHeight-1) {
                continue;
            }else{

                //show_debug_message(string(rx) + " and " + string(ry));
                if (groups[get2DIndex(rx/(corridoorWidth+1), ry/(corridoorWidth+1), groupWidth)] != groups[get2DIndex(destx/(corridoorWidth+1), desty/(corridoorWidth+1), groupWidth)]) {
                    //Not connected
                    //show_debug_message("connecting");

                    //engine->log("D: " + rx.toString() + " : " + ry.toString());

                    if (dir == 0) {
                        for (int i = 0; i < corridoorWidth; i++) {
                            tileSystem->SetBlock(Maths::Vector2<int>(destx-1, desty+i), 2);
                        }
                    }else if (dir == 1) {
                        for (int i = 0; i < corridoorWidth; i++) {
                            tileSystem->SetBlock(Maths::Vector2<int>(destx+corridoorWidth, desty+i), 2);
                        }
                    }else if (dir == 2) {
                        for (int i = 0; i < corridoorWidth; i++) {
                            tileSystem->SetBlock(Maths::Vector2<int>(destx+i, desty-1), 2);
                        }
                    }else if (dir == 3) {
                        for (int i = 0; i < corridoorWidth; i++) {
                            tileSystem->SetBlock(Maths::Vector2<int>(destx+i, desty+corridoorWidth), 2);
                        }
                    }

                    int oldGroup = groups[get2DIndex(destx/(corridoorWidth+1), desty/(corridoorWidth+1), groupWidth)];
                    int currentGroup = groups[get2DIndex(rx/(corridoorWidth+1), ry/(corridoorWidth+1), groupWidth)];
                    groups[get2DIndex(destx/(corridoorWidth+1), desty/(corridoorWidth+1), groupWidth)] = currentGroup;

                    int otherGroups = 0;

                    for (int ix = 0; ix < (double)tilesWidth/(corridoorWidth+1)-1; ix++) {
                        for (int iy = 0; iy < (double)tilesHeight/(corridoorWidth+1)-1; iy++) {
                            //if (ix > 0 && ix < width-1 && iy > 0 && iy < height-1){
                            if (groups[get2DIndex(ix, iy, groupWidth)] == oldGroup) {
                                groups[get2DIndex(ix, iy, groupWidth)] = currentGroup;
                            }else if (groups[get2DIndex(ix, iy, groupWidth)] == currentGroup) {
                            }else{
                                otherGroups++;
                            }
                            //}
                        }
                    }

                    //this->SetGenerationPercentage(std::max((((double)(group-otherGroups)/group)*100), this->GetGenerationPercentage()));

                    if (otherGroups == 0) {
                        connected = true;
                        //engine->log("All connected!");

                        PopulateMaze(tileSystem, engine, true, 1);

                        tileSystem->CreateTiles();
                        tileSystem->CommitTiles();

                        this->respawnPoint = Maths::Vector2<double>(tileSystem->tileSize*(corridoorWidth/2+1)-16, tileSystem->tileSize*(startHeight+corridoorWidth/2)-16);

                        this->SetComplete();

                        /*auto player = new TestEntity(engine, level);
                        player->AddViewportTrack(mainViewport);*/

                        //mainViewport.Zoom(0.25);

                        /*playerObj = instance_create(global.block_size*(corridoor_width/2+1)-16, global.block_size*(startHeight+corridoor_width/2)-16, player);

                           view_wview[0]= 1200;
                           view_hview[0]= 900;
                           view_vborder[0] = view_wview[0];
                           view_hborder[0] = view_hview[0];
                           view_object[0] = playerObj;*/
                    }

                }else{
                    continue;
                    //show_debug_message("Already connected!");
                }

            }
        }
    }
}
