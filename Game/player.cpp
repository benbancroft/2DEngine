#include "player.h"

void Player::Loaded(Core::Engine* engine){
    Entity::Loaded(engine);

    Maths::Vector2<int> res = engine->GetResolution();
    x = res.GetX()/2;
    y = res.GetY()/2;

    speed = 0;

    //SetAlarm(0, 150);
}

void Player::Tick(Core::Engine *engine){
    Entity::Tick(engine);

    if (hasTarget){
        double distance = Maths::distanceBetweenPoints(Maths::Vector2<double>(x, y), target);
        if (distance <= speed){
            speed = 0;
            x = target.GetX();
            y = target.GetY();
            hasTarget = false;
        }
    }
}

void Player::Render(Core::Render *render){
    Entity::Render(render);
}

void Player::Alarm(int index){
    if (index == 0){
        DEBUG_LOG_WRITE_V("Alarm", "Alarm Entity");
        SetAlarm(0, 150);
    }
}

void Player::OnTouchPress(double x, double y){

    speed = 0.5;

    target = Maths::Vector2<double>(x, y);
    hasTarget = true;

    this->DirectTowards(target);

    //this->x = target.GetX();
    //this->y = target.GetY();

    DEBUG_LOG_WRITE_V("Tick", "Press again");
    DEBUG_LOG_PRINT_V("Engine", "press X: %f Y: %f current X: %f Y: %f angle: %f", x, y, this->x, this->y, this->direction);
}

void Player::OnTouchDrag(double x, double y){
    DEBUG_LOG_WRITE_V("Tick", "Drag again");
    DEBUG_LOG_PRINT_V("Engine", "drag X: %f Y: %f", x, y);
}
