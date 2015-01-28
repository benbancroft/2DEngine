#ifndef ENTITY_H
#define ENTITY_H

#include "engine.h"
#include "level.h"
#include "viewport.h"
#include "depthrenderable.h"
#include "platform/platform_log.h"

namespace Core
{
    class Engine;
    class Viewport;
    class Level;
    //class DepthRenderable;

    struct AlarmData{
        int startTime = 0;
        int delay = 0;

        AlarmData(){}
        AlarmData(int startTime, int delay){
            this->startTime = startTime;
            this->delay = delay;
        }
    };

    class Entity : public DepthRenderable
    {
        Level* level;

        void addRenderable(Level* level);

    public:
        std::vector<Viewport*> viewportsFollowing;

        virtual void test(){
            DEBUG_LOG_WRITE_D("TST", "base");
        }

        Entity(Engine* engine, Level* level) : DepthRenderable(7){
            //registerEntity(self, engine);
            this->level = level;
            addRenderable(level);
        }

        void SetAlarm(int index, int ticks);
        void AddViewportTrack(Viewport* viewport);
        void DirectTowards(Maths::Vector2<double> position);

        void SetPosition(Maths::Vector2<double> position);

        virtual void Loaded(Engine *engine);
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

        double width = 32.0;
        double height = 32.0;

        bool slides = false;

        std::string spriteSheet = "";
        int spriteIndex = 0;

        std::map<int, AlarmData> alarms;
    };
}

#endif // ENTITY_H
