#include "mazegenerator.h"

int get2DIndex(int x, int y, int width){
    return x*width+y;
}

void MazeGenerator::Loaded(Core::Engine* engine){

    Core::TileSystem* tileSystem = GetTileSystem();

    int tilesWidth = 20;
    int tilesHeight = 20;

    tilesWidth -= (tilesWidth % (corridoorWidth+1))-1;
    tilesHeight -= (tilesHeight % (corridoorWidth+1))-1;

    generateSpeed = ceil(sqrt(tilesWidth*tilesHeight)*0.1);

    //blocks = new List<int>(get2DIndex(tilesWidth, tilesHeight, tilesWidth));
    groups = std::vector<int>(get2DIndex(tilesWidth/(corridoorWidth+1), tilesHeight/(corridoorWidth+1), tilesWidth/(corridoorWidth+1)));

    group = 0;

    //Create solid maze
    for (int ix=0; ix<tilesWidth; ix++){
        for (int iy=0; iy<tilesHeight; iy++){
            tileSystem->SetBlock(Maths::Vector2<int>(ix, iy), 1);
        }
    }

    /*for (int iy=0; iy<tilesHeight; iy++){
    String line = "";
    for (int ix=0; ix<tilesWidth; ix++){
    int blockId = blocks[get2DIndex(ix, iy, tilesWidth)];
    if (blockId == 1){
    line = line + "W";
    }else{
    line = line + " ";
    }
    }
    Engine.log(line);
    }

    Engine.log("CW:" + corridoorWidth.toString() + "TileW: " + tilesWidth.toString() + " TileH: " + tilesHeight.toString());*/

    //Give structure
    for (int ix=0; ix<tilesWidth; ix++){
        for (int iy=0; iy<tilesHeight; iy++){
            int blockId = tileSystem->GetBlock(Maths::Vector2<int>(ix, iy));
            if (blockId != 1){
                //global.blocks[ix, iy] = 1;
            }
            else if (ix % (corridoorWidth+1) == 1 && iy % (corridoorWidth+1) == 1 && ix > 0 && ix < tilesWidth-1 && iy > 0 && iy < tilesHeight-1){
                    groups[get2DIndex(ix/(corridoorWidth+1), iy/(corridoorWidth+1), tilesWidth/(corridoorWidth+1))] = group++;
                for (int i = 0; i < corridoorWidth; i++){
                    for (int j = 0; j < corridoorWidth; j++){
                        tileSystem->SetBlock(Maths::Vector2<int>(ix+i, iy+j), /*-2*/2);
                    }
                }
                tileSystem->SetBlock(Maths::Vector2<int>(ix, iy), /*-1*/2);

                //ds_list_insert(intersections, 0, pos);

                //show_debug_message("DB: " + string(ix/2) + " and " + string(iy/2));
                //instance_create(ix*32,iy*32, example_block);
            }else{
                tileSystem->SetBlock(Maths::Vector2<int>(ix, iy), 1);
            }
        }
    }
}

void MazeGenerator::Tick(Core::Engine* engine){
    if (connected == false){
        //engine->SetSeed(seed);

        /*int rx = 1+engine->RandomInteger(0, (tilesWidth)~/(corridoorWidth+1))*(corridoorWidth+1);
        int ry = 1+engine->RandomInteger(0, (tilesHeight)~/(corridoorWidth+1))*(corridoorWidth+1);*/
    }else{
    }
}
