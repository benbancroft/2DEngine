#include "tiles/tilesystem.h"

namespace Core {

TileSystem::TileSystem(Level* level, TileGenerator* generator, std::string tilesheetUrl, int tileSize, int chunkSize){
    this->level = level;
    this->generator = generator;
    this->tileSize = tileSize;
    this->chunkSize = chunkSize;
    this->tilesheetUrl = tilesheetUrl;

    generator->SetLevel(level);
    generator->SetTileSystem(this);

    //if level has bounds check to see if boundx,y mod chunksize is zero
    //attach generator...
}

void TileSystem::Render(Core::Render *render){
    for (const auto& kv : this->tileChunks) {
        //kv.second->Render(kv.first, render);
    }
}

void TileSystem::Loaded(Engine* engine){
    if (generator != NULL) {
        generator->RegisterBlocks(engine);
        generator->Loaded(engine);
    }
}

bool TileSystem::ResolveCollision(double currentX, double currentY, double *newX, double *newY, double aabbWidth, double aabbHeight, bool canSlide){

    int obj_index = 0;

    double deltaY = *newY - currentY;
    double deltaX = *newX - currentX;

    double angle = atan2(deltaY, deltaX);

    double xFactor = 1;
    double yFactor = 1;

    double collisionX = *newX;
    double collisionY = *newY;
    double collisionOffset = 0;
    int collisionSide = 0;
    bool outsideGrid = false;
    bool touchingWall = false;

    int currentBlockX = floor(currentX/this->tileSize);
    int currentBlockY = floor(currentY/this->tileSize);

    int newBlockX = floor(collisionX/this->tileSize);
    int newBlockY = floor(collisionY/this->tileSize);

    //show_debug_message("DX: " + string(deltaX) + " DY: " + string(deltaY));

    int dir = 0;

    if (deltaY == 0 || deltaX == 0) {
        yFactor = 0;
        xFactor = 0;
        //show_debug_message("no yFactor");
    }else{
        yFactor = tan(angle);
        if (yFactor != 0)
            xFactor =  1 / tan(angle);
        else
            xFactor = 0;
        //show_debug_message("yfactor");
    }
    yFactor=deltaY;
    xFactor=deltaX;
    //wrong!
    if (/*angle > -(1/2) * Maths::PI && angle < (1/2) * Maths::PI*/deltaX > 0) {
        dir = 1;
        currentBlockX = floor((currentX+aabbWidth)/this->tileSize);
        //currentBlockY = floor((currentY)/this->tileSize);

        newBlockX = floor((collisionX+aabbWidth)/this->tileSize);
        //newBlockY = floor((collisionY)/this->tileSize);
    }else if(/*angle < -(1/2) * Maths::PI || angle > (1/2) * Maths::PI*/ deltaX < 0) {
        dir = -1;
    }else{
        dir = 0;
    }

    double xXColPos = 0;
    double xYColPos = 0;
    double yXColPos = 0;
    double yYColPos = 0;

    bool wasCollision = false;

    //int sCornerX = floor(aabbWidth/this->tileSize);

    //fix!
    if (dir != 0) {
        for (int d = 0; d <= ceil(abs(newBlockX-currentBlockX)); d++) {
            bool breakLoop = false;

            int checkBlockX = currentBlockX+dir*d;
            int sCornerY = floor((fmod(currentY+((checkBlockX*this->tileSize)-currentX)*yFactor,this->tileSize)+aabbHeight)/this->tileSize);

            for (int i = 0; i <= sCornerY; i++) {

                int checkBlockY = 0;
                //if (dir == 1) {
                    //checkBlockX = currentBlockX+d;
                    //checkBlockY = floor((currentY+(i*this->tileSize)*yFactor)/this->tileSize)+i;

                //}else{
                    //checkBlockX = currentBlockX-d;
                    checkBlockY = floor(currentY/this->tileSize+d*yFactor)+i;
                //}
                int blockId = this->GetBlock(Maths::Vector2<int>(checkBlockX, checkBlockY));
                if (blockId != 0 && this->GetBlockById(blockId)->isSolid) {
                    auto test = currentY/this->tileSize+d*yFactor+i;
                    //if (i == 0  && test == checkBlockY){
                        //if (i == 0) {
                            //DEBUG_LOG_WRITE_D("TAG", "Touch");
                        //}
                    //}else{
                        xXColPos = (checkBlockX-dir)*this->tileSize;
                        if (dir == 1) xXColPos += this->tileSize-aabbWidth;
                        xYColPos = (currentY+dir*(xXColPos-currentX)*yFactor);
                        //if (dir == 1) collisionX -= aabbWidth;

                        //collisionY = (checkBlockY-dir)*this->tileSize;

                        //collisionX = (currentX+(collisionY-currentY)*xFactor);

                        wasCollision = true;

                        breakLoop = true;
                        break;
                   //}
                }
            }
            if (breakLoop) {
                break;
            }
        }
    }

    int yDir = 0;
    if (deltaY > 0) {
        yDir = 1;
        //currentBlockX = floor((currentX)/this->tileSize);
        currentBlockY = floor((currentY+aabbHeight)/this->tileSize);

        //newBlockX = floor((collisionX)/this->tileSize);
        newBlockY = floor((collisionY+aabbHeight)/this->tileSize);
    }else if (deltaY < 0) {
        yDir = -1;
    }else{
        yDir = 0;
    }

    //dir, currentY, currentBlockY, newBlockY

    if (true == false && yDir != 0) {
        for (int d = 0; d <= ceil(abs(newBlockY-currentBlockY)); d++) {
            bool breakLoop = false;

            int checkBlockY = currentBlockY+yDir*d;
            int sCornerX = floor((fmod(currentX+((checkBlockY*this->tileSize)-currentY)*xFactor,this->tileSize)+aabbWidth)/this->tileSize);

            for (int i = 0; i <= sCornerX; i++) {

                int checkBlockX = 0;
                /*if (yDir == 1) {
                    checkBlockX = floor((currentX+(d*this->tileSize)*xFactor)/this->tileSize)+i;

                }else{
                    checkBlockX = floor((currentX+(-d*this->tileSize)*xFactor)/this->tileSize)+i;
                }*/
                checkBlockX = floor(currentX/this->tileSize+d*xFactor)+i;

                int blockId = this->GetBlock(Maths::Vector2<int>(checkBlockX, checkBlockY));
                //tile_is_wall(checkBlockX, checkBlockY, obj_index) || get_block_at(checkBlockX, checkBlockY) == noone
                if (blockId != 0 && this->GetBlockById(blockId)->isSolid) {

                    /*if ((currentY+d*yFactor)/this->tileSize+i == checkBlockY){
                        DEBUG_LOG_WRITE_D("TAG", "Touch");
                    }else{*/

                        yYColPos = (checkBlockY-yDir)*this->tileSize;
                        if (yDir == 1) yYColPos += this->tileSize-aabbHeight;

                        yXColPos = (currentX+(yYColPos-currentY)*xFactor);

                        //collisionY = (currentY+(collisionX-currentX)*yFactor);

                        wasCollision = true;

                        breakLoop = true;
                    //}

                }
            }
            if (breakLoop) {
                break;
            }
        }
    }

    /*if (xXColPos != 0 || yXColPos != 0){
        double slideX = currentX;
        double slideY = currentY;
        if (xXColPos != false && xYColPos != false && Maths::distanceBetweenPoints(Maths::Vector2<double>(xXColPos, xYColPos), Maths::Vector2<double>(currentX, currentY)) < Maths::distanceBetweenPoints(Maths::Vector2<double>(yXColPos, yYColPos), Maths::Vector2<double>(currentX, currentY))){
            collisionX = xXColPos;
            collisionY = xYColPos;
            //show_debug_message("Use X" + string(collisionX));
            if (dir == -1){
                //show_debug_message("Side: LEFT");
                collisionSide = 0;
            }else if (dir == 1){
                //show_debug_message("Side: RIGHT");
                collisionSide = 1;
            }

            if (canSlide == true){
                    slideX = collisionX;
                    slideY = *newY;
            }
        }else{
            collisionX = yXColPos;
            collisionY = yYColPos;
            //show_debug_message("Use Y" + string(collisionY));
            if (yDir == -1)
                //show_debug_message("Side: UP");
                collisionSide = 2;
            else if (yDir == 1){
                //show_debug_message("Side: DOWN");
                collisionSide = 3;
            }

            if (canSlide == true){
                slideX = *newX;
                slideY = collisionY;
            }

        }
        collisionOffset = Maths::distanceBetweenPoints(Maths::Vector2<double>(collisionX, collisionY), Maths::Vector2<double>(*newX, *newY));
        touchingWall = true;
        if (canSlide == true){
            bool slideResult = this->ResolveCollision(collisionX, collisionY, &slideX, &slideY, aabbWidth, aabbHeight, false);
            collisionOffset = 0;
        }
       }*/

    if (outsideGrid == true) {
        collisionOffset = 0;
    }

    if (wasCollision){
        *newX = collisionX;
        *newY = collisionY;
    }

    /*returnData[0] = collisionX;
       returnData[1] = collisionY;
       returnData[2] = collisionOffset;
       returnData[3] = collisionSide;
       returnData[4] = outsideGrid;
       returnData[5] = touchingWall;

       return returnData;      */
    return wasCollision;

}

void TileSystem::Tick(Engine* engine){
    if (generator != NULL) {
        generator->Tick(engine);
    }
}

Block* TileSystem::GetBlockById(int blockId){
    auto it = blocks.find(blockId);

    if (it != blocks.end()) {
        return it->second;
    }else
        return NULL;
}

TileChunk* TileSystem::GetChunk(Maths::Vector2<int> chunkPosition, bool create){
    auto chunkIter = tileChunks.find(chunkPosition);
    TileChunk* chunk = NULL;
    if (chunkIter != tileChunks.end()) chunk = chunkIter->second;
    else if (create) {
        chunk = new TileChunk(this, chunkPosition);
        this->tileChunks[chunkPosition] = chunk;
    }
    return chunk;
}


void TileSystem::SetBlock(Maths::Vector2<int> position, int blockId){
    auto chunkPosition = position.Clone()/chunkSize;

    auto chunk = GetChunk(chunkPosition);

    chunk->SetBlock(position%chunkSize, blockId);
}

int TileSystem::GetBlock(Maths::Vector2<int> position){
    auto chunkPosition = position.Clone()/chunkSize;

    auto chunk = GetChunk(chunkPosition, false);

    if (chunk != NULL) {
        return chunk->GetBlock(position%chunkSize);
    }else{
        return 0;
    }
}

void TileSystem::RegisterBlockType(int blockId, Block* block){
    blocks[blockId] = block;
}

void TileSystem::CreateTile(int depth, Maths::Vector2<int> position, Maths::Vector2<int> tile, bool createChunk){
    auto chunkPosition = Maths::Vector2<int>(position.GetX(), position.GetY())/chunkSize;
    TileChunk* chunk = GetChunk(chunkPosition, createChunk);
    if (chunk != NULL) {
        chunk->CreateTile(depth,position%chunkSize,tile);
    }
}

void TileSystem::CreateTiles(){

    for (const auto& kv : tileChunks) {
        TileChunk* chunk = kv.second;
        if (chunk->NeedsUpdate()) chunk->CreateTiles();
    }
}

void TileSystem::CommitTiles(){

    for (const auto& kv : tileChunks) {
        TileChunk* chunk = kv.second;
        chunk->CommitTiles();
    }
}

}
