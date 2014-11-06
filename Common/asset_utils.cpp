#include "asset_utils.h"
#include "platform/platform_asset_utils.h"
#include "platform/platform_log.h"
#include "texture.h"
#include <assert.h>
#include <stdlib.h>

#define TAG "Assets"

namespace Assets {

    bool load_asset(std::string relative_path, AssetType type) {
        if (relative_path.empty()) return false;
        
        switch(type){
         case TEXTURE:
            {
                const Platform::FileData file = Platform::get_asset_data(relative_path + ".png");
                
                Texture texture(type, relative_path);
                texture.loadTexture(&file);
                
                Platform::release_asset_data(&file);
                
                assetList.push_back(texture);
                
                DEBUG_LOG_WRITE_D(TAG, ("Loaded texture: " + relative_path).c_str());
            }
         break;
        }
        
        return true;
    }
    
    Asset* get_asset(std::string relative_path){
    
        for(std::vector<Asset>::iterator it = assetList.begin(); it != assetList.end(); ++it) {
            if ((*it).getUrl() == relative_path) return &*it;
        }
        
        return NULL;
    
    }
    
    GLuint build_program_from_assets(const char* vertex_shader_path, const char* fragment_shader_path) {
        assert(vertex_shader_path != NULL);
        assert(fragment_shader_path != NULL);

        const Platform::FileData vertex_shader_source = Platform::get_asset_data(vertex_shader_path);
        const Platform::FileData fragment_shader_source = Platform::get_asset_data(fragment_shader_path);
        const GLuint program_object_id = Assets::build_program(
            (const GLchar *)vertex_shader_source.data, vertex_shader_source.data_length,
            (const GLchar *)fragment_shader_source.data, fragment_shader_source.data_length);

        release_asset_data(&vertex_shader_source);
        release_asset_data(&fragment_shader_source);

        return program_object_id;

    }

}
