#ifndef TESTENTITY_H
#define TESTENTITY_H

#include "entity.h"

class TestEntity : public Core::Entity
{
public:
    void Loaded(Core::Engine* engine);
    void Tick(Core::Engine *engine);
    void Render(Core::Render *render);
    void Alarm(int index);
};

#endif // TESTENTITY_H
