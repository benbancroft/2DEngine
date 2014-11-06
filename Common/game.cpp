#include <iostream>
#include <map>

#include "game.h"
#include "asset.h"
#include "asset_utils.h"
#include "texture.h"
#include "platform/platform_gl.h"

#include "platform/platform_asset_utils.h"
#include "shader.h"

#include "buffer.h"

/*#include "asset_utils.h"
#include "buffer.h"
#include "image.h"
#include "platform_asset_utils.h"
#include "shader.h"
#include "texture.h"*/

static std::map <std::string, Assets::Asset> assetList;

static Assets::Texture* texture;
static GLuint buffer;
static GLuint program;

static GLint a_position_location;
static GLint a_texture_coordinates_location;
static GLint u_texture_unit_location;

// position X, Y, texture S, T
static const float rect[] = {-1.0f, -1.0f, 0.0f, 0.0f,
-1.0f, 1.0f, 0.0f, 1.0f,
1.0f, -1.0f, 1.0f, 0.0f,
1.0f, 1.0f, 1.0f, 1.0f};

void on_surface_created() {
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}

void on_surface_changed() {
    Assets::load_asset("textures/air_hockey_surface", Assets::TEXTURE);
    texture = Assets::get_texture("textures/air_hockey_surface");
    //texture = load_png_asset_into_texture("textures/air_hockey_surface.png");
    buffer = create_vbo(sizeof(rect), rect, GL_STATIC_DRAW);
    program = Assets::build_program_from_assets("shaders/shader.vsh", "shaders/shader.fsh");

    a_position_location = glGetAttribLocation(program, "a_Position");
    a_texture_coordinates_location = glGetAttribLocation(program, "a_TextureCoordinates");
    u_texture_unit_location = glGetUniformLocation(program, "u_TextureUnit");
}

void on_draw_frame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

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
}
