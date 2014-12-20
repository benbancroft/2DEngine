#include "shader.h"
//#include "platform/platform_gl.h"
#include "platform/platform_log.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define TAG "Shaders"

namespace Assets {

static void log_v_fixed_length(const GLchar* source, const GLint length) {
    if (LOGGING_ON) {
        char log_buffer[length + 1];
        memcpy(log_buffer, source, length);
        log_buffer[length] = '\0';

        DEBUG_LOG_WRITE_V(TAG, log_buffer);
    }
}

static void log_shader_info_log(GLuint shader_object_id) {
    if (LOGGING_ON) {
        GLint log_length;
        glGetShaderiv(shader_object_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar log_buffer[log_length];
        glGetShaderInfoLog(shader_object_id, log_length, NULL, log_buffer);

        DEBUG_LOG_WRITE_V(TAG, log_buffer);
    }
}

static void log_program_info_log(GLuint program_object_id) {
    if (LOGGING_ON) {
        GLint log_length;
        glGetProgramiv(program_object_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar log_buffer[log_length];
        glGetProgramInfoLog(program_object_id, log_length, NULL, log_buffer);

        DEBUG_LOG_WRITE_V(TAG, log_buffer);
    }
}

void Shader::LoadShader(const Platform::FileData* shader, GLenum type) {

    GLuint shader_object_id = glCreateShader(type);
    GLint compile_status;

    assert(shader_object_id != 0);

    glShaderSource(shader_object_id, 1, (const GLchar **)&shader->data, (const GLint*)&shader->data_length);
    glCompileShader(shader_object_id);
    glGetShaderiv(shader_object_id, GL_COMPILE_STATUS, &compile_status);

    if (LOGGING_ON) {
        DEBUG_LOG_WRITE_D(TAG, "Results of compiling shader source:");
        log_v_fixed_length((const GLchar*)shader->data, shader->data_length);
        log_shader_info_log(shader_object_id);
    }

    DEBUG_LOG_WRITE_D(TAG, "Compile Status: ");
    DEBUG_LOG_WRITE_D(TAG, compile_status == 0 ? "FALSE" : "TRUE");

    if (type == GL_VERTEX_SHADER){
        this->vertex = shader_object_id;
    }else if(type == GL_FRAGMENT_SHADER){
        this->fragment = shader_object_id;
    }

    DEBUG_LOG_WRITE_D(TAG, "Set shader");

    assert(compile_status != 0);
}

void Shader::LinkShaders() {
    GLuint program_object_id = glCreateProgram();
    GLint link_status;

    assert(program_object_id != 0);

    glAttachShader(program_object_id, this->vertex);
    glAttachShader(program_object_id, this->fragment);
    glLinkProgram(program_object_id);
    glGetProgramiv(program_object_id, GL_LINK_STATUS, &link_status);

    if (LOGGING_ON) {
        DEBUG_LOG_WRITE_D(TAG, "Results of linking program:");
        log_program_info_log(program_object_id);
    }

    assert(link_status != 0);

    DEBUG_LOG_PRINT_D(TAG, "Results of linking program: %d %d", program_object_id ,this->GetProgram());

    validate_program(program_object_id);

    this->SetProgram(program_object_id);

    //this->SetProgram(1000);

    //this->program = program_object_id;
    //this->program = 0;
}

/*GLuint build_program(
    const GLchar * vertex_shader_source, const GLint vertex_shader_source_length,
    const GLchar * fragment_shader_source, const GLint fragment_shader_source_length) {
    assert(vertex_shader_source != NULL);
    assert(fragment_shader_source != NULL);

    GLuint vertex_shader = compile_shader(
        GL_VERTEX_SHADER, vertex_shader_source, vertex_shader_source_length);
    GLuint fragment_shader = compile_shader(
        GL_FRAGMENT_SHADER, fragment_shader_source, fragment_shader_source_length);
    return link_program(vertex_shader, fragment_shader);
   }*/

GLint validate_program(const GLuint program) {
    //if (LOGGING_ON) {
        int validate_status;

        glValidateProgram(program);
        glGetProgramiv(program, GL_VALIDATE_STATUS, &validate_status);
        DEBUG_LOG_PRINT_D(TAG, "Results of validating program: %d", validate_status);
        log_program_info_log(program);
        return validate_status;
    //}

    return 0;
}

GLuint Shader::GetProgram(){
    return this->program;
}

void Shader::SetProgram(GLuint program){
    this->program = program;
}

Shader* GetShader(std::string relative_path){
    Asset* assetClass = get_asset(relative_path);

    if (assetClass == NULL || assetClass->getType() != SHADER) return NULL;

    Shader* shader = static_cast<Shader *>(assetClass);

    if (shader) return shader;

    return NULL;
}

}
