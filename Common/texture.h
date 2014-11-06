#ifndef TEXTURE_H
#define TEXTURE_H

#include "platform/platform_gl.h"
#include "platform/platform_file_utils.h"
#include "asset.h"
#include "asset_utils.h"

namespace Assets
{

    class Texture : public Asset
    {
        using Asset::Asset;
    
        GLuint texture;

    public:
       GLuint getTexture();
       bool loadTexture(const Platform::FileData* data);
    };
    
    Texture* get_texture(std::string relative_path);

}

#endif
