#include "texture.h"
#include "image_utils.h"
#include "platform/platform_gl.h"
#include <assert.h>

namespace Assets {

    GLuint Texture::getTexture(){
        return this->texture;
    }

    bool Texture::loadTexture(const Platform::FileData* file){

        const ImageUtils::RawImageData raw_image_data = ImageUtils::get_raw_image_data_from_png(file->data, static_cast<unsigned int>(file->data_length));
        
        GLuint texture_object_id;
        glGenTextures(1, &texture_object_id);
        assert(texture_object_id != 0);

        glBindTexture(GL_TEXTURE_2D, texture_object_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, raw_image_data.gl_color_format, raw_image_data.width, raw_image_data.height, 0, raw_image_data.gl_color_format, GL_UNSIGNED_BYTE, raw_image_data.data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        
        this->texture = texture_object_id;

        release_raw_image_data(&raw_image_data);

        return true;
    }

    Texture* get_texture(std::string relative_path){
        Asset* assetClass = get_asset(relative_path);
        
        if (assetClass == NULL || assetClass->getType() != TEXTURE) return NULL;
        
        Texture* texture = static_cast<Texture *>(assetClass);
        
        if (texture) return texture;
        
        return NULL;
    }

}
