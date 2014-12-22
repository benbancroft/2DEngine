#include "testentity.h"

void TestEntity::Loaded(Core::Engine* engine){
    Entity::Loaded(engine);

    Maths::Vector2<int> res = engine->GetResolution();
    x = res.GetX()/2;
    y = res.GetY()/2;

    speed = 0.05;

    SetAlarm(0, 150);
}

void TestEntity::Tick(Core::Engine *engine){
    Entity::Tick(engine);
}

void TestEntity::Render(Core::Render *render){
    Entity::Render(render);
}

void TestEntity::Alarm(int index){
    if (index == 0){
        DEBUG_LOG_WRITE_V("Alarm", "Alarm Entity");
        SetAlarm(0, 150);
    }
}
