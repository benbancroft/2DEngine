#include "engine.h"

namespace Core {

    Engine::Engine(){

    }

    void Engine::setLoading(bool state){
        if (state == true){
            isLoaded = false;
            isLoading = true;
        }else{
            isLoading = false;
        }
    }

    void Engine::SurfaceCreated() {

        setLoading(true);

        DEBUG_LOG_WRITE_V("Render", "Surface created");

        Assets::LoadAsset("textures/air_hockey_surface", Assets::TEXTURE);
        Assets::LoadAsset("shaders/shader", Assets::SHADER);
    }

    void Engine::RecreateGLContext(){
        setLoading(true);
        //Should only really be ran for Android
        Assets::ReloadAssets();
        setLoading(false);
    }

    void Engine::SurfaceChanged(int width, int height) {

        this->InitiseRenderer();
        this->SetResolution(Maths::Vector2<int>(width, height));

        setLoading(false);
    }

    void Engine::Animate(double currentTime){
        if (isLoading == false && isLoaded == false){
            lastTime = currentTime;
            unprocessedFrames = 0;
            isLoaded = true;
            if (!beenLoaded) {
                beenLoaded = true;
                Loaded();
            }
        }else{
            unprocessedFrames += (long)((currentTime-lastTime)*60.0/1000); // 60 fps

            //max lag compensation
            if (unprocessedFrames > 10) unprocessedFrames = 10;
            while (unprocessedFrames > 1) {
                this->Tick();
                unprocessedFrames -= 1;
            }
            this->Render();
        }
    }

    void Engine::Loaded(){
        std::for_each(levels.begin(), levels.end(), [this](Level* level){ level->Loaded(this);});
    }

    void Engine::Tick(){
        //DEBUG_LOG_WRITE_V("Tick", "Ticking again");

        std::for_each(levels.begin(), levels.end(), [this](Level* level){ level->Tick(this);});
    }

    void Engine::Render() {

        this->ResetRenderer(true);

        std::for_each(viewports.begin(), viewports.end(), [this](Viewport* viewport){ viewport->Render(this); });
    }

    //Input

    void Engine::OnTouchPress(double x, double y){
        //DEBUG_LOG_WRITE_V("Tick", "Press again");
        //DEBUG_LOG_PRINT_V("Engine", "press X: %f Y: %f", x, y);

        std::for_each(viewports.begin(), viewports.end(), [x, y](Viewport* viewport){ viewport->OnTouchPress(x, y); });
    }

    void Engine::OnTouchDrag(double x, double y){
        //DEBUG_LOG_WRITE_V("Tick", "Drag again");
        //DEBUG_LOG_PRINT_V("Engine", "drag X: %f Y: %f", x, y);

        std::for_each(viewports.begin(), viewports.end(), [x, y](Viewport* viewport){ viewport->OnTouchDrag(x, y); });
    }

    //API

    Level* Engine::RegisterLevel(Level* level){
        levels.push_back(level);
        level->Loaded(this);
        return level;
    }

    Viewport* Engine::RegisterViewport(Viewport* viewport){
        viewports.push_back(viewport);
        return viewport;
    }

}
