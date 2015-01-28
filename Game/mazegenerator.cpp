#include "mazegenerator.h"

int get2DIndex(int x, int y, int width){
    return x*width+y;
}

void MazeGenerator::Loaded(Core::Engine* engine){

    Core::TileSystem* tileSystem = GetTileSystem();

    tilesWidth -= (tilesWidth % (corridoorWidth+1))-1;
    tilesHeight -= (tilesHeight % (corridoorWidth+1))-1;

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
}

void MazeGenerator::Tick(Core::Engine* engine){
    if (connected == false) {

        Core::TileSystem* tileSystem = GetTileSystem();

        engine->SetSeed(seed);

        int groupWidth = tilesWidth/(corridoorWidth+1);

        for (int r=0; r<generateSpeed; r++) {
            /*int rx = engine->RandomInteger(0, ((tilesWidth/(corridoorWidth+1)-1)*(corridoorWidth+1)).toInt());
               int ry = engine->RandomInteger(1, ((tilesHeight/(corridoorWidth+1)-1)*(corridoorWidth+1)).toInt());*/

            int rx = 1+engine->RandomInteger(0, (tilesWidth)/(corridoorWidth+1))*(corridoorWidth+1);
            int ry = 1+engine->RandomInteger(0, (tilesHeight)/(corridoorWidth+1))*(corridoorWidth+1);

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

                    for (int ix = 0; ix < tilesWidth/(corridoorWidth+1)-1; ix++) {
                        for (int iy = 0; iy < tilesHeight/(corridoorWidth+1)-1; iy++) {
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

                    this->SetGenerationPercentage(std::max((((double)(group-otherGroups)/group)*100), this->GetGenerationPercentage()));

                    if (otherGroups == 0) {
                        connected = true;
                        //engine->log("All connected!");

                        tileSystem->CreateTiles();
                        tileSystem->CommitTiles();

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
