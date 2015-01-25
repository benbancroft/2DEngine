#include "asset_utils.h"
#include "platform/platform_asset_utils.h"
#include "platform/platform_log.h"
#include "texture.h"
#include <assert.h>
#include <stdlib.h>

#define TAG "Assets"

namespace Assets {

    Asset* loadAssetInstance(Asset* asset, AssetType type, const std::string relative_path){
        switch(type){
         case TEXTURE:
            {
                Platform::FileData file = Platform::get_asset_data(relative_path + ".png");

                if (asset == NULL) asset = new Texture(type, relative_path);
                //Texture* texture = (Texture*)asset;
                static_cast<Texture*>(asset)->loadTexture(&file);

                Platform::release_asset_data(&file);

                DEBUG_LOG_WRITE_D(TAG, ("Loaded texture: " + relative_path).c_str());
            }
            break;
         case SHADER:
        {
            Platform::FileData vertexShader = Platform::get_asset_data(relative_path + ".vsh");
            Platform::FileData fragmentShader = Platform::get_asset_data(relative_path + ".fsh");

            if (asset == NULL) asset = new Shader(type, relative_path);
            //Shader* shader = (Shader*)asset;
            static_cast<Shader*>(asset)->LoadShader(&vertexShader, GL_VERTEX_SHADER);
            static_cast<Shader*>(asset)->LoadShader(&fragmentShader, GL_FRAGMENT_SHADER);
            static_cast<Shader*>(asset)->LinkShaders();

            DEBUG_LOG_WRITE_D(TAG, "DONE SHADER");

            Platform::release_asset_data(&vertexShader);
            Platform::release_asset_data(&fragmentShader);

            DEBUG_LOG_WRITE_D(TAG, "DONE SHADER UNLOAD");

        }
         break;
        }
        return asset;
    }

    void LoadAsset(const std::string relative_path, AssetType type, Asset* asset) {
        if (relative_path.empty()) return;

        bool assetExists = asset != NULL;

        //if (!assetExists) asset = new Asset(type, relative_path);

        //Asset* asset = new Asset(type, relative_path);

        asset = loadAssetInstance(asset, type, relative_path);

        DEBUG_LOG_PRINT_D(TAG, "DONE LOAD ASSET %s", asset->getUrl().c_str());

        if (!assetExists) assetList.push_back(asset);

        DEBUG_LOG_WRITE_D(TAG, "DONE PUSH ASSET");
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

        //DEBUG_LOG_WRITE_V(TAG, ("Finding asset: " + relative_path).c_str());
    
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
