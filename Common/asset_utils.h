#ifndef ASSET_UTILS_H
#define ASSET_UTILS_H

#include <stdio.h>
#include <vector>

#include "platform/platform_gl.h"
#include "asset.h"

//REMOVE!
#include "shader.h"

namespace Assets
{

static std::vector <Asset> assetList;

bool load_asset(std::string relative_path, AssetType type);
Asset* get_asset(std::string relative_path);
GLuint build_program_from_assets(const char* vertex_shader_path, const char* fragment_shader_path);

}

#endif
