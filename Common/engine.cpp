#include "engine.h"

namespace Core {

    static Assets::Texture* texture;
    static GLuint buffer;
    static Assets::Shader* program;

    static GLint a_position_location;
    static GLint a_texture_coordinates_location;
    static GLint u_texture_unit_location;

    // position X, Y, texture S, T
    static const float rect[] = {-1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f};

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

        glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

        Assets::LoadAsset("textures/air_hockey_surface", Assets::TEXTURE);
        Assets::LoadAsset("shaders/shader", Assets::SHADER);
        DEBUG_LOG_WRITE_D("Render", "SHADER INIT LOAD");
        //texture = Assets::GetAsset<Assets::Texture>("textures/air_hockey_surface");
        //texture = load_png_asset_into_texture("textures/air_hockey_surface.png");

        setLoading(false);
    }

    void Engine::RecreateGLContext(){
        setLoading(true);
        //Should only really be ran for Android
        Assets::ReloadAssets();
        setLoading(false);
    }

    void Engine::SurfaceChanged(int width, int height) {

        this->width = width;
        this->height = height;

        texture = Assets::GetTexture("textures/air_hockey_surface");

        DEBUG_LOG_WRITE_V("Render", "Got texture");

        buffer = create_vbo(sizeof(rect), rect, GL_STATIC_DRAW);
        //program = Assets::build_program_from_assets("shaders/shader.vsh", "shaders/shader.fsh");
        program = Assets::GetShader("shaders/shader");

        //DEBUG_LOG_WRITE_V("Render", "Surface shaders linked");

        a_position_location = glGetAttribLocation(program->GetProgram(), "a_Position");
        a_texture_coordinates_location = glGetAttribLocation(program->GetProgram(), "a_TextureCoordinates");
        u_texture_unit_location = glGetUniformLocation(program->GetProgram(), "u_TextureUnit");
    }

    void Engine::Animate(double currentTime){
        if (isLoading == false && isLoaded == false){
            lastTime = currentTime;
            unprocessedFrames = 0;
            isLoaded = true;
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

    void Engine::Tick(){
        //DEBUG_LOG_WRITE_V("Tick", "Ticking again");

        std::for_each(levels.begin(), levels.end(), [](Level* level){ level->Tick();});
    }

    void Engine::Render() {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        glUseProgram(program->GetProgram());

        //DEBUG_LOG_WRITE_V("Render", "Rending again");

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getTexture());
        glUniform1i(u_texture_unit_location, 0);

        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glVertexAttribPointer(a_position_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), BUFFER_OFFSET(0));
        glVertexAttribPointer(a_texture_coordinates_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), BUFFER_OFFSET(2 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(a_position_location);
        glEnableVertexAttribArray(a_texture_coordinates_location);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        std::for_each(viewports.begin(), viewports.end(), [this](Viewport* viewport){ viewport->Render(this); });
    }

    //API

    Maths::Vector2<int> Engine::GetResolution(){
        return Maths::Vector2<int>(width, height);
    }

    Level* Engine::RegisterLevel(Level* level){
        levels.push_back(level);
        //level->SetEngine(this);
        return level;
    }

}
