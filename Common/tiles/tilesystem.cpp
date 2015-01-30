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

int toBlockComponent(double comp, double tileSize, bool up = false){
    if (up)
        return (int)ceil(comp/tileSize);
    else
        return (int)floor(comp/tileSize);
}

bool scanForEdgeCollision(double collisionX, double collisionY, double aabbWidth, double aabbHeight, TileSystem* tileSystem, bool farSide, bool flipAxis = false){

    if (flipAxis){
        std::swap(collisionX, collisionY);
        std::swap(aabbWidth, aabbHeight);
    }
    if (farSide){
        collisionY += aabbHeight;
    }

    int yBlock = toBlockComponent(collisionY, tileSystem->tileSize);
    int startX = toBlockComponent(collisionX, tileSystem->tileSize);
    int endX = toBlockComponent((collisionX+aabbWidth), tileSystem->tileSize);
    int dir = farSide ? 0 : 1;

    for (int xBlock = startX; xBlock <= endX; xBlock++) {
        int blockId = 0;
        if (flipAxis){
            blockId = tileSystem->GetBlock(Maths::Vector2<int>(yBlock-dir, xBlock));
        }else{
            blockId = tileSystem->GetBlock(Maths::Vector2<int>(xBlock, yBlock-dir));
        }
        if (blockId != 0 && tileSystem->GetBlockById(blockId)->isSolid) {
            return true;
        }
    }
    return false;
}

CollisionSide TileSystem::ResolveCollision(double currentX, double currentY, double *newX, double *newY, double aabbWidth, double aabbHeight, bool canSlide){

    double deltaY = *newY - currentY;
    double deltaX = *newX - currentX;

    double angle = atan2(deltaY, deltaX);

    CollisionSide collisionState = CollisionSide::None;
    bool isTouching = false;

    double xFactor = 1;
    double yFactor = 1;

    double collisionX = currentX;
    double collisionY = currentY;

    int xDir = 0;

    if (deltaY == 0 || deltaX == 0) {
        yFactor = 0;
        xFactor = 0;
    }else{
        yFactor = tan(angle);
        if (yFactor != 0)
            xFactor =  1 / tan(angle);
        else
            xFactor = 0;
    }
    yFactor=deltaY;
    xFactor=deltaX;

    if (deltaX > 0) {
        xDir = 1;
    }else if(deltaX < 0) {
        xDir = -1;
    }else{
        xDir = 0;
    }

    int yDir = 0;
    if (deltaY > 0) {
        yDir = 1;
    }else if (deltaY < 0) {
        yDir = -1;
    }else{
        yDir = 0;
    }

    while (xDir != 0 && yDir != 0) {
        double xDist = 0;
        double yDist = 0;

        if (yDir < 0) {
            yDist = std::fabs(collisionY - (double)(toBlockComponent(collisionY, this->tileSize)*this->tileSize));
        }else{
            yDist = std::fabs(collisionY+aabbHeight - (toBlockComponent(collisionY+aabbHeight, this->tileSize, true)*this->tileSize));
        }

        //Check for touching on Y side that we are traveling in.
        if (yDist == 0){
            isTouching = scanForEdgeCollision(collisionX, collisionY, aabbWidth, aabbHeight, this, yDir > 0, false);
            collisionState = yDir > 0 ? CollisionSide::Bottom : CollisionSide::Top;
        }

        if (xDir < 0) {
            xDist = std::fabs(collisionX - (toBlockComponent(collisionX, this->tileSize)*this->tileSize));
        }else{
            xDist = std::fabs(collisionX+aabbWidth - (toBlockComponent(collisionX+aabbWidth, this->tileSize, true)*this->tileSize));
        }

        //Check for touching on Y side that we are traveling in.
        if (isTouching == false && xDist == 0){
            isTouching = scanForEdgeCollision(collisionX, collisionY,aabbWidth, aabbHeight, this, xDir > 0, true);
            collisionState = xDir > 0 ? CollisionSide::Right : CollisionSide::Left;
        }

        if (!isTouching && ((yDist <= xDist  && yDist != 0) || (xDist == 0)) && yDist < std::fabs(collisionY - *newY)) {
            double tXdist = (yDist*yDir)/yFactor*xFactor;

            bool wasCollision = scanForEdgeCollision(collisionX+tXdist, collisionY+yDist*yDir,aabbWidth, aabbHeight, this, yDir > 0, false);

            if (wasCollision){
                collisionState = yDir > 0 ? CollisionSide::Bottom : CollisionSide::Top;
            }

            collisionY += yDist*yDir;
            collisionX += tXdist;
        }else if (!isTouching && xDist != 0 && xDist < yDist && xDist < std::fabs(collisionX - *newX)) {
            double tYdist = (xDist*xDir)/xFactor*yFactor;

            bool wasCollision = scanForEdgeCollision(collisionX+xDist*xDir, collisionY+tYdist,aabbWidth, aabbHeight, this, xDir > 0, true);

            if (wasCollision){
                collisionState = xDir > 0 ? CollisionSide::Right : CollisionSide::Left;
            }

            collisionX += xDist*xDir;
            collisionY += tYdist;
        }else{
            if (isTouching){
                //Do nothing
            }else{
                collisionState = CollisionSide::None;
                collisionX = *newX;
                collisionY = *newY;
            }
            break;
        }

        if (collisionState != CollisionSide::None) {
            break;
        }
    }

    if (collisionState != CollisionSide::None || isTouching) {

        if (canSlide){
            double slideX = collisionX;
            double slideY = collisionY;
            switch(collisionState){
            case Top:
            case Bottom:
                slideX = *newX;
                break;
            case Left:
            case Right:
                slideY = *newY;
                break;
            }
            ResolveCollision(collisionX, collisionY, &slideX, &slideY, aabbWidth, aabbHeight, false);

            collisionX = slideX;
            collisionY = slideY;

        }

        *newX = collisionX;
        *newY = collisionY;
    }
    return collisionState;

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
