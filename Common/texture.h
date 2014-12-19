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
    
        GLuint texture;

    public:
        Texture(AssetType type, std::string url) : Asset(type, url) {}
        GLuint getTexture();
        bool loadTexture(const Platform::FileData* data);
    };
    
    Texture* GetTexture(std::string relative_path);

}

#endif
