#ifndef MAINLEVEL_H
#define MAINLEVEL_H

#include "level.h"
#include "platform/platform_log.h"

class MainLevel : public Core::Level
{
public:
    MainLevel(int width, int height) : Core::Level::Level(width, height){}

    void Tick();
    void Render();
};

#endif // MAINLEVEL_H
