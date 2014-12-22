#include "game.h"

using namespace Core;

Engine* InitialiseGame(){
    return new Game();
}


Game::Game()
{
}

void Game::Loaded(){
    Engine::Loaded();

    Maths::Vector2<int> resolution = this->GetResolution();
    mainLevel = this->RegisterLevel(new MainLevel(resolution.GetX()*2, resolution.GetY()*2));
    mainViewport = this->RegisterViewport(new Core::Viewport(mainLevel, 0.0, 0.0, resolution.GetX(), resolution.GetY(), resolution.GetX()/2, resolution.GetY()/2, resolution.GetX(), resolution.GetY()));
    mainLevel->AddEntity(new TestEntity(), this);
}
