#ifndef GAME_H
#define GAME_H

#include "engine.h"

Core::Engine* InitialiseGame();


class Game : public Core::Engine
{

public:
Game();
};

#endif // GAME_H
