#include "viewport.h"

namespace Core {

    Viewport::Viewport(Level* level, double x, double y, int width, int height, double levelX, double levelY, int levelWidth, int levelHeight){
        this->level = level;
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->levelX = levelX;
        this->levelY = levelY;
        this->levelWidth = levelWidth;
        this->levelHeight = levelHeight;
    }

    void Viewport::Render(Core::Render *render){
        render->SetViewport(Maths::Vector2<float>(x, y), Maths::Vector2<int>(width, height));
        render->SetViewportScene(Maths::Vector2<float>(levelX, levelY), Maths::Vector2<int>(levelWidth, levelHeight));
        render->SetUseViewport(true);

        level->Render(render);

        render->SetUseViewport(false);
    }

}
