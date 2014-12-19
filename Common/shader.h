#ifndef SHADER_H
#define SHADER_H

#include "platform/platform_gl.h"
#include "asset.h"
#include "asset_utils.h"
#include "platform/platform_gl.h"
#include "platform/platform_asset_utils.h"

namespace Assets
{

    enum ShaderType { VERTEX, FRAGMENT };

    class Shader : public Asset
    {
        using Asset::Asset;
    
        GLuint vertex;
        GLuint fragment;
        GLuint program;

        GLint linkShader();

    public:
        void LoadShader(const Platform::FileData* shader, GLenum type);
        GLint ValidateShader();
        void LinkShaders();

        GLuint GetProgram();

       /*GLuint getTexture();
       bool loadTexture(const Platform::FileData* data);*/
       //GLuint compileShader(ShaderType type, const unsigned char* source, const unsigned int length);
    };

    Shader* GetShader(std::string relative_path);

    //REMOVE!
    GLuint compile_shader(const GLenum type, const GLchar* source, const GLint length);
    GLuint link_program(const GLuint vertex_shader, const GLuint fragment_shader);
    GLuint build_program(
	const GLchar * vertex_shader_source, const GLint vertex_shader_source_length,
	const GLchar * fragment_shader_source, const GLint fragment_shader_source_length);

    GLint validate_program(const GLuint program);
    
}

#endif
