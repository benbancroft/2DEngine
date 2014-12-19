#ifndef MAINLEVEL_H
#define MAINLEVEL_H

#include "level.h"
#include "platform/platform_log.h"

class MainLevel : public Core::Level
{
    using Core::Level::Level;
public:
    void Tick();
    void Render();
};

#endif // MAINLEVEL_H
