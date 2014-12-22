#include "entity.h"

namespace Core {

    Entity::Entity()
    {
    }

    void Entity::Loaded(Engine* engine){
    }

    void Entity::DirectTowards(Maths::Vector2<double> position){
        this->direction = Maths::PI/2 + atan2(position.GetY()-y, position.GetX()-x);
    }

    void Entity::Tick(Engine* engine){
        //DEBUG_LOG_WRITE_V("Tick", "Ticking Entity");
    }

    void Entity::Render(Core::Render *render){
        //DEBUG_LOG_WRITE_V("Render", "Rendering Entity");

        render->SetColour(Maths::Vector4<float>(0.0,1.0,0.0,1.0));
        render->SetUseColour(true);
        render->SetDimensions(Maths::Vector2<int>(20,20));
        render->Draw(Maths::Vector2<float>(x, y));
    }

    void Entity::SetAlarm(int index, int ticks){
        this->alarms[index] = AlarmData(aliveTime, ticks);
    }

    void Entity::Alarm(int index){
    }

}
