#ifndef MAINLEVEL_H
#define MAINLEVEL_H

#include "level.h"
#include "tiles/tilelayer.h"
#include "tiles/tilegenerator.h"
#include "platform/platform_log.h"

class MainLevel : public Core::Level
{
    Core::TileSystem* tileSystem;
public:
    MainLevel(int width, int height) : Core::Level::Level(width, height){
        tileSystem = new Core::TileSystem(this, new Core::TileGenerator(), "textures/tilesheet", 64, 10);
    }

    void Render(Core::Render* render);

    void Loaded(Core::Engine *engine);

    void Tick(Core::Engine *engine);
};

#endif // MAINLEVEL_H
