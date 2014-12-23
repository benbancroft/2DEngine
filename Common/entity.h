#ifndef ENTITY_H
#define ENTITY_H

#include "engine.h"
#include "viewport.h"
#include "platform/platform_log.h"

namespace Core
{
    class Engine;
    class Viewport;

    struct AlarmData{
        int startTime = 0;
        int delay = 0;

        AlarmData(){}
        AlarmData(int startTime, int delay){
            this->startTime = startTime;
            this->delay = delay;
        }
    };

    class Entity
    {
    public:
        Entity();

        void SetAlarm(int index, int ticks);
        void DirectTowards(Maths::Vector2<double> position);

        virtual void Loaded(Engine* engine);
        virtual void Tick(Engine *engine);
        virtual void Render(Core::Render *render);
        virtual void Alarm(int index);

        virtual void OnTouchPress(double x, double y);
        virtual void OnTouchDrag(double x, double y);

        int aliveTime = 0;

        double x = 0.0;
        double y = 0.0;
        double lastX = 0.0;
        double lastY = 0.0;
        double direction = 0.0;
        double speed = 0.0;

        int depth = 1;

        std::string spriteSheet = "";
        int spriteIndex = 0;

        std::map<int, AlarmData> alarms;
    };
}

#endif // ENTITY_H
