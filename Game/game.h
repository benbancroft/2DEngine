#ifndef GAME_H
#define GAME_H

#include "engine.h"
#include "level.h"
#include "vector.h"

#include "mainlevel.h"
#include "testentity.h"

Core::Engine* InitialiseGame();


class Game : public Core::Engine
{
    Core::Level* mainLevel;
    Core::Viewport* mainViewport;

public:
Game();
void Loaded();
};

#endif // GAME_H
