#ifndef RENDER_H
#define RENDER_H

#include <assert.h>

#include "platform/platform_gl.h"
#include "vector.h"
#include "texture.h"

enum ShaderType { None, Draw ,Tile };

namespace Core
{

    struct RenderState{

        bool isInitialised = false;

        //GLSL
        //All shaders
        GLint colourLocation = NULL;
        GLint useColourBlendLocation = NULL;
        GLint resolutionLocation = NULL;
        GLint dimensionLocation = NULL;
        GLint depthLocation = NULL;
        GLint textureSampleLocation = NULL;
        GLint useViewportLocation = NULL;
        GLint viewportSettingsLocation = NULL;
        GLint viewportSceneSettingsLocation = NULL;

        GLint verticiesLocation;

        ShaderType shaderType = None;

        //Draw shader
        GLint useColourLocation = NULL;
        GLint positionLocation = NULL;
        GLint uvLocation = NULL;

        //Tile shader
        GLint tileMapSquareSizeLocation = NULL;
        GLint tileMapChunkSizeLocation = NULL;
        GLint tileMapOffsetLocation = NULL;
        GLint tileMapSeperationLocation = NULL;
        GLint tileMapLocation = NULL;
        GLint tileSheetSquareSizeLocation = NULL;
        GLint tileSheetSizeLocation = NULL;

        GLuint shader;
        GLuint texture;

        Maths::Vector2<float> dimensions;
        int depth = 0;
        std::string textureURL = "";
        bool useColourState = false;
        bool useColourBlendState = false;
        bool useAlphaState = false;
        Maths::Vector4<float> colour;
        std::string shaderURL = "";
        Maths::Vector2<int> resolution;

        bool useViewport = false;
        Maths::Vector2<float> vpTopLeft;
        Maths::Vector2<int> vpDimensions;

        Maths::Vector2<float> vpsTopLeft;
        Maths::Vector2<int> vpsDimensions;
    };

    class Render
    {
        RenderState renderState;
        void setHasRenderState(bool state){ renderState.isInitialised = state; }
        bool hasRenderState() { return renderState.isInitialised; }
    public:
        Render();
        void InitiseRenderer();
        void ResetRenderer(bool isDraw);
        virtual void SetDimensions(Maths::Vector2<float> dimensions, bool force = false);
        void SetTexture(std::string url, bool force = false);
        void SetDepth(int depth, bool force = false);
        void SetUseColour(bool state, bool force = false);
        void SetUseAlpha(bool state, bool force = false);
        void SetUseColourBlending(bool state, bool force = false);
        void SetColour(Maths::Vector4<float> colour, bool force = false);
        void SetShader(std::string url, ShaderType type, bool force = false);
        void SetResolution(Maths::Vector2<int> resolution, bool force = false);
        virtual void SetUseSprite(std::string url, int index, double xScale = 1.0, double yScale = 1.0);

        void SetUseViewport(bool useViewportState, bool force = false);
        void SetViewport(Maths::Vector2<float> position, Maths::Vector2<int> dimensions, bool force = false);
        void SetViewportScene(Maths::Vector2<float>  position, Maths::Vector2<int> dimensions, bool force = false);

        virtual void Draw(Maths::Vector2<float> position);

        virtual void DrawTileChunk(Maths::Vector2<int> location, std::string tileSheet, int squareSize, int chunkSize, GLuint chunkData);

        Maths::Vector2<int> GetResolution();

    };

}

#endif // RENDER_H
