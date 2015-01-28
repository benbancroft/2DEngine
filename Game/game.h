#ifndef GAME_H
#define GAME_H

#include "engine.h"
#include "level.h"
#include "vector.h"

#include "mainlevel.h"
#include "player.h"

Core::Engine* InitialiseGame();


class Game : public Core::Engine
{
    MainLevel* mainLevel;
    Core::Viewport* mainViewport;
    Core::TileSystem* tileSystem;
    MazeGenerator* generator;
    Player* player = NULL;

public:
    Game();
    void Loaded();
    void Tick();
};

#endif // GAME_H
