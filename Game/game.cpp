#include "game.h"

using namespace Core;

Engine* InitialiseGame(){
    return new Game();
}


Game::Game()
{
}

void Game::Loaded(){

    generator =  new MazeGenerator();

    Maths::Vector2<int> resolution = this->GetResolution();
    mainLevel = new MainLevel(resolution.GetX()*2, resolution.GetY()*2);
    this->RegisterLevel(mainLevel);

    tileSystem = new Core::TileSystem(mainLevel, generator, "textures/tilesheet", 64, 10);
    mainLevel->SetTileSystem(tileSystem);
    tileSystem->Loaded(this);

    mainViewport = this->RegisterViewport(new Core::Viewport(mainLevel, 0, 0, resolution.GetX(), resolution.GetY(), resolution.GetX()/2, resolution.GetY()/2, resolution.GetX(), resolution.GetY()));

    Engine::Loaded();
}

void Game::Tick(){

    if (player == NULL && generator->IsComplete()){
        player = new Player(this, mainLevel);
        player->SetPosition(generator->GetRespawnPoint());
        player->AddViewportTrack(mainViewport);
    }

    Engine::Tick();
}
