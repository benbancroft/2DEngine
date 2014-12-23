#ifndef TESTENTITY_H
#define TESTENTITY_H

#include "entity.h"

class TestEntity : public Core::Entity
{
    bool hasTarget = false;
    Maths::Vector2<double> target;
public:
    void Loaded(Core::Engine* engine);
    void Tick(Core::Engine *engine);
    void Render(Core::Render *render);
    void Alarm(int index);

    void OnTouchPress(double x, double y);

    void OnTouchDrag(double x, double y);
};

#endif // TESTENTITY_H
