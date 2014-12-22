#include "render.h"

namespace Core {

    Render::Render()
    {
    }

    GLuint createVBO(const GLsizeiptr size, const GLvoid* data, const GLenum usage) {
        assert(data != NULL);
        GLuint vbo_object;
        glGenBuffers(1, &vbo_object);
        assert(vbo_object != 0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_object);
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        return vbo_object;
    }

    void Render::InitiseRenderer(){
        setHasRenderState(true);

        SetShader("shaders/shader", true);
        renderState.shaderType = ShaderType::Draw;

        static const float rect[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 1.0f};

        createVBO(sizeof(rect), rect, GL_STATIC_DRAW);

        renderState.colourLocation = glGetUniformLocation(renderState.shader, "u_colour");
        renderState.useColourBlendLocation = glGetUniformLocation(renderState.shader, "u_useColourBlend");
        renderState.resolutionLocation = glGetUniformLocation(renderState.shader, "u_resolution");
        renderState.dimensionLocation = glGetUniformLocation(renderState.shader, "u_dimension");
        renderState.depthLocation = glGetUniformLocation(renderState.shader, "u_depth");
        renderState.textureSampleLocation = glGetUniformLocation(renderState.shader, "u_textureSample");
        renderState.useViewportLocation = glGetUniformLocation(renderState.shader, "u_useViewport");
        renderState.viewportSettingsLocation = glGetUniformLocation(renderState.shader, "u_viewport");
        renderState.viewportSceneSettingsLocation = glGetUniformLocation(renderState.shader, "u_viewportScene");


        if (renderState.shaderType == ShaderType::Draw){
            renderState.uvLocation = glGetUniformLocation(renderState.shader, "u_uvs");
            renderState.positionLocation = glGetUniformLocation(renderState.shader, "u_position");
            renderState.useColourLocation = glGetUniformLocation(renderState.shader, "u_useColour");
        }

        /*if (renderState.shaderType == ShaderType::TILE){
            renderState.tileMapSquareSizeLocation = glGetUniformLocation(renderState.shader, "u_mapSquareSize");
            renderState.tileMapSizeLocation = glGetUniformLocation(renderState.shader, "u_mapSize");
            renderState.tileMapOffsetLocation = glGetUniformLocation(renderState.shader, "u_mapOffsetSize");
            renderState.tileMapSeperationLocation = glGetUniformLocation(renderState.shader, "u_mapSeperationSize");
            renderState.tileMapLocation = glGetUniformLocation(renderState.shader, "u_mapTile");
            renderState.tileSheetSizeLocation = glGetUniformLocation(renderState.shader, "u_tileSheetSize");
        }*/

        renderState.verticiesLocation = glGetAttribLocation(renderState.shader, "a_verticies");
        glEnableVertexAttribArray(renderState.verticiesLocation);

        glVertexAttribPointer(renderState.verticiesLocation, 2, GL_FLOAT, false, 0, 0);

        SetResolution(renderState.resolution, true);
        SetUseColour(false, true);
        SetColour(renderState.colour, true);

        //SetTexture(this.textureURL);
        glUniform1i(renderState.textureSampleLocation, 0);

        SetUseViewport(renderState.useViewport, true);
        SetViewport(renderState.vpTopLeft, renderState.vpDimensions, true);
        //correct?
        SetViewportScene(renderState.vpsTopLeft, renderState.vpsDimensions, true);

        SetDimensions(renderState.dimensions, true);
        SetDepth(renderState.depth, true);

        ResetRenderer(false);
    }

    void Render::ResetRenderer(bool isDraw){
        if (isDraw){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
        }
        SetUseAlpha(true, true);
        SetUseColourBlending(false, true);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Render::SetDimensions(Maths::Vector2<int> dimensions, bool force){
        if (!hasRenderState() || (!force && renderState.dimensions == dimensions)) return;
        renderState.dimensions = dimensions;
        glUniform2f(renderState.dimensionLocation, dimensions.GetX(), dimensions.GetY());
    }

    void Render::SetTexture(std::string url, bool force){
        if (!hasRenderState() || (!force && url == renderState.textureURL)) return;
        auto texture = Assets::GetTexture(url);
        if (texture != NULL){
            renderState.textureURL = url;
            renderState.texture = texture->getTexture();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture->getTexture());
        }
    }

    void Render::SetDepth(int depth, bool force){
        if (!hasRenderState() || (!force && depth == renderState.depth)) return;
        renderState.depth = depth;
        glUniform1i(renderState.depthLocation, depth);
    }

    void Render::SetUseColour(bool state, bool force){
        if (!hasRenderState() || (!force && state == renderState.useColourState)) return;
        renderState.useColourState = state;
        glUniform1i(renderState.useColourLocation, state ? 1 : 0);
    }

    void Render::SetUseAlpha(bool state, bool force){
        if (!hasRenderState() || (!force && state == renderState.useAlphaState)) return;
        if (state == true){
            glEnable(GL_BLEND);
        }else{
            glDisable(GL_BLEND);
        }
        renderState.useAlphaState = state;
    }

    void Render::SetUseColourBlending(bool state, bool force){
        if (!hasRenderState() || (!force && state == renderState.useColourBlendState)) return;
        renderState.useColourBlendState = state;
        glUniform1i(renderState.useColourBlendLocation, state ? 1 : 0);
    }

    void Render::SetColour(Maths::Vector4<float> colour, bool force){
        if (!hasRenderState() || (!force && colour == renderState.colour)) return;
        renderState.colour = colour;
        glUniform4f(renderState.colourLocation, colour.GetX(),colour.GetY(), colour.GetZ(), colour.GetW());
    }

    void Render::SetShader(std::string url, bool force){
        if (!hasRenderState() || (!force && url == renderState.shaderURL)) return;
        auto shader = Assets::GetShader(url);
        if (shader != NULL){
            renderState.shaderURL = url;
            renderState.shader = shader->GetProgram();
            glUseProgram(shader->GetProgram());
        }
    }

    void Render::SetResolution(Maths::Vector2<int> resolution, bool force){
        if (!hasRenderState() || (!force && resolution == renderState.resolution)) return;
        renderState.resolution = resolution;
        glUniform2f(renderState.resolutionLocation, resolution.GetX(), resolution.GetY());
    }

    Maths::Vector2<int> Render::GetResolution(){
        if (!hasRenderState()) return NULL;
        return renderState.resolution;
    }

    void Render::SetUseSprite(std::string url, int index, double xScale, double yScale){
    }

    void Render::SetUseViewport(bool useViewportState, bool force){
        if (!hasRenderState() || (!force && useViewportState == renderState.useViewport)) return;
        renderState.useViewport = useViewportState;
        glUniform1i(renderState.useViewportLocation, useViewportState ? 1 : 0);
    }

    void Render::SetViewport(Maths::Vector2<float> position, Maths::Vector2<int> dimensions, bool force){
        if (!hasRenderState() || (!force && renderState.vpTopLeft == position && renderState.vpDimensions == dimensions)) return;

        renderState.vpTopLeft = position;
        renderState.vpDimensions = dimensions;

        float matrix[] = {position.GetX(), position.GetY(), (float)dimensions.GetX(), (float)dimensions.GetY()};

        glUniformMatrix2fv(renderState.viewportSettingsLocation, 1, false, matrix);
    }

    void Render::SetViewportScene(Maths::Vector2<float>  position, Maths::Vector2<int>  dimensions, bool force){
        if (!hasRenderState() || (!force && renderState.vpsTopLeft == position && renderState.vpsDimensions == dimensions)) return;

        renderState.vpsTopLeft = position;
        renderState.vpsDimensions = dimensions;

        float matrix[] = {position.GetX(), position.GetY(), (float)dimensions.GetX(), (float)dimensions.GetY()};

        glUniformMatrix2fv(renderState.viewportSceneSettingsLocation, 1, false, matrix);
    }

    void Render::Draw(Maths::Vector2<float> position){
        if (!hasRenderState()) return;
        if (renderState.shaderType == ShaderType::Draw){
            glUniform2f(renderState.positionLocation, position.GetX(), position.GetY());
        }
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

}
