#ifndef MAINLEVEL_H
#define MAINLEVEL_H

#include "level.h"
#include "tilelayer.h"
#include "tilegenerator.h"
#include "platform/platform_log.h"

class MainLevel : public Core::Level
{
    Core::TileSystem* tileSystem;
    Core::TileLayer* mainLayer;
public:
    MainLevel(int width, int height) : Core::Level::Level(width, height){
        tileSystem = new Core::TileSystem(this, new Core::TileGenerator(), 32, 10);
    }

    void Render(Core::Render* render);

    void Loaded(Core::Engine *engine);

    void Tick(Core::Engine *engine);
};

#endif // MAINLEVEL_H
