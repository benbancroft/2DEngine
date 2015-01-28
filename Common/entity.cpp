#include "entity.h"

namespace Core {

    void Entity::addRenderable(Level *level){
        level->AddRenderable(this);
    }

    void Entity::Loaded(Engine* engine){
    }

    void Entity::SetPosition(Maths::Vector2<double> position){
        this->x = position.GetX();
        this->y = position.GetY();
    }

    void Entity::AddViewportTrack(Viewport *viewport){
        if (viewport->level == this->level && std::find(viewportsFollowing.begin(), viewportsFollowing.end(), viewport) == viewportsFollowing.end()){
            viewportsFollowing.push_back(viewport);
        }
    }

    void Entity::DirectTowards(Maths::Vector2<double> position){
        this->direction = -Maths::PI/2 + atan2(position.GetX()-x,position.GetY()-y);
    }

    void Entity::Tick(Engine* engine){
        //test();
        //DEBUG_LOG_WRITE_V("Tick", "Ticking Entity");
    }

    void Entity::Render(Core::Render *render){
        //DEBUG_LOG_WRITE_V("Render", "Rendering Entity");

        render->SetShader("shaders/draw", ShaderType::Draw);
        render->SetDepth(depth, true);
        render->SetColour(Maths::Vector4<float>(1.0,1.0,0.0,1.0));
        render->SetUseColour(true);
        render->SetDimensions(Maths::Vector2<float>(width,height));
        render->Draw(Maths::Vector2<float>(x, y));
    }

    void Entity::SetAlarm(int index, int ticks){
        this->alarms[index] = AlarmData(aliveTime, ticks);
    }

    void Entity::Alarm(int index){
    }

    void Entity::OnTouchPress(double x, double y){
    }

    void Entity::OnTouchDrag(double x, double y){
    }

}
