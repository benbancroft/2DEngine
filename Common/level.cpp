#include "level.h"

using namespace Core;

namespace Core {

    void Level::AddEntity(Entity* entity, Engine* engine){
        entities.push_back(entity);
        entity->Loaded(engine);
    }

    void Level::Tick(Engine* engine){

        auto entityMoveUpdate = [](Entity* entity){
            entity->x += cos(entity->direction) * entity->speed;
            entity->y -= sin(entity->direction) * entity->speed;
        };

        auto entityAlarmUpdate = [](Entity* entity){

            std::vector<int> toRemove;

            auto iterateAlarms = [&](std::pair<int, AlarmData> element) {
                int offset = entity->aliveTime - element.second.startTime;
                if(offset > element.second.delay){
                    toRemove.push_back(element.first);

                }
            };
            std::for_each(entity->alarms.begin(), entity->alarms.end(), iterateAlarms);
            auto processAlarm = [entity](int key){
                entity->alarms.erase(key);
                entity->Alarm(key);
            };
            std::for_each(toRemove.begin(), toRemove.end(), processAlarm);
        };

        std::for_each(entities.begin(), entities.end(), [engine, entityAlarmUpdate, entityMoveUpdate](Entity* entity) {
            entityAlarmUpdate(entity);
            entity->Tick(engine);
            entity->aliveTime++;
            entityMoveUpdate(entity);
        });
        //DEBUG_LOG_WRITE_V("Tick", "Ticking base level");
    }

    void Level::Loaded(Engine* engine){
        std::for_each(entities.begin(), entities.end(), [engine](Entity* entity){ entity->Loaded(engine); });
    }

    void Level::Render(Core::Render *render){
        std::for_each(entities.begin(), entities.end(), [render](Entity* entity){ entity->Render(render); });
    }

    void Level::OnTouchPress(double x, double y){
        std::for_each(entities.begin(), entities.end(), [x, y](Entity* entity){ entity->OnTouchPress(x, y); });
    }

    void Level::OnTouchDrag(double x, double y){
        std::for_each(entities.begin(), entities.end(), [x, y](Entity* entity){ entity->OnTouchDrag(x, y); });
    }
}
