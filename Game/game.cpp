#include "game.h"

using namespace Core;

Engine* InitialiseGame(){
    return new Game();
}


Game::Game()
{
    Maths::Vector2<int> resolution = this->GetResolution();
    mainLevel = this->RegisterLevel(new MainLevel(resolution.GetX()*2, resolution.GetY()*2));
}
