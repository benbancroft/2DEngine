#ifndef TESTENTITY_H
#define TESTENTITY_H

#include "entity.h"
#include "engine.h"

class Player : public Core::Entity
{
    using Core::Entity::Entity;

    bool hasTarget = false;
    Maths::Vector2<double> target;
public:

    virtual void test(){
        DEBUG_LOG_WRITE_D("TST", "derived");
    }

    Player(Core::Engine* engine, Core::Level* level) : Entity(engine, level){
        //Entity::registerEntity(this, engine);
        level->AddEntity(this, engine);

    }

    void Loaded(Core::Engine* engine);
    void Tick(Core::Engine *engine);
    void Render(Core::Render *render);
    void Alarm(int index);

    void OnTouchPress(double x, double y);

    void OnTouchDrag(double x, double y);
};

#endif // TESTENTITY_H
