#ifndef GAME_H
#define GAME_H

#include "engine.h"
#include "level.h"
#include "vector.h"

#include "mainlevel.h"

Core::Engine* InitialiseGame();


class Game : public Core::Engine
{
    Core::Level* mainLevel;

public:
Game();
};

#endif // GAME_H
