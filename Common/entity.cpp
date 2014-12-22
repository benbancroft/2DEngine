#include "entity.h"

namespace Core {

    Entity::Entity()
    {
    }

    void Entity::Tick(Engine* engine){
        //DEBUG_LOG_WRITE_V("Tick", "Ticking Entity");
    }

    void Entity::Render(Core::Render *render){
        //DEBUG_LOG_WRITE_V("Render", "Rendering Entity");

        render->SetColour(Maths::Vector4<float>(0.0,1.0,0.0,1.0));
        render->SetUseColour(true);
        render->SetDimensions(Maths::Vector2<int>(20,20));
        auto res = render->GetResolution();
        render->Draw(Maths::Vector2<float>(res.GetX()/2, res.GetY()/2));
    }

}
