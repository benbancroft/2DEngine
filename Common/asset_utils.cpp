#include "asset_utils.h"
#include "platform/platform_asset_utils.h"
#include "platform/platform_log.h"
#include "texture.h"
#include <assert.h>
#include <stdlib.h>

#define TAG "Assets"

namespace Assets {

    void loadAssetInstance(Asset* asset){
        switch(asset->getType()){
         case TEXTURE:
            {
                Platform::FileData file = Platform::get_asset_data(asset->getUrl() + ".png");


                Texture* texture = (Texture*)asset;
                texture->loadTexture(&file);

                Platform::release_asset_data(&file);

                DEBUG_LOG_WRITE_D(TAG, ("Loaded texture: " + asset->getUrl()).c_str());
            }
            break;
         case SHADER:
        {
            Platform::FileData vertexShader = Platform::get_asset_data(asset->getUrl() + ".vsh");
            Platform::FileData fragmentShader = Platform::get_asset_data(asset->getUrl() + ".fsh");

            Shader* shader = (Shader*)asset;
            shader->LoadShader(&vertexShader, GL_VERTEX_SHADER);
            shader->LoadShader(&fragmentShader, GL_FRAGMENT_SHADER);
            shader->LinkShaders();

            Platform::release_asset_data(&vertexShader);
            Platform::release_asset_data(&fragmentShader);

        }
         break;
        }
    }

    bool LoadAsset(const std::string relative_path, AssetType type, Asset* asset) {
        if (relative_path.empty()) return false;

        bool assetExists = asset != NULL;

        if (!assetExists) asset = new Asset(type, relative_path);

        //Asset* asset = new Asset(type, relative_path);

        loadAssetInstance(asset);

        if (!assetExists) assetList.push_back(asset);
        
        return true;
    }

    void ReloadAssets(){
        for (std::vector<Asset*>::const_iterator iterator = assetList.begin(), end = assetList.end(); iterator != end; ++iterator) {
            Asset* asset = *iterator;

            DEBUG_LOG_WRITE_D("TAG", "Reload");

            LoadAsset(asset->getUrl(), asset->getType(), asset);

            DEBUG_LOG_WRITE_D("TAG", "Reloaded");
        }
    }
    
    Asset *get_asset(std::string relative_path){

        DEBUG_LOG_WRITE_V(TAG, ("Finding asset: " + relative_path).c_str());
    
        for(std::vector<Asset*>::iterator it = assetList.begin(); it != assetList.end(); ++it) {
            if ((*it)->getUrl() == relative_path) return *it;
        }
        
        DEBUG_LOG_WRITE_V(TAG, "Could not find asset - could not be loaded");

        return NULL;
    
    }
    
    /*GLuint build_program_from_assets(const char* vertex_shader_path, const char* fragment_shader_path) {
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

    }*/

}
