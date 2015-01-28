#ifndef MAINLEVEL_H
#define MAINLEVEL_H

#include "level.h"
#include "tiles/tilelayer.h"
#include "mazegenerator.h"
#include "platform/platform_log.h"

class MainLevel : public Core::Level
{
public:
    MainLevel(int width, int height) : Core::Level::Level(width, height){
    }

    void Render(Core::Render* render);

    void Loaded(Core::Engine *engine);

    void Tick(Core::Engine *engine);
};

#endif // MAINLEVEL_H
