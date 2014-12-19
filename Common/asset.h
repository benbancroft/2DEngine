#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <map>
namespace Assets
{

    enum AssetType { SHADER, TEXTURE, SPRITE_SHEET, TILE_SHEET };
    //template<typename T> T* GetAsset(std::string relative_path);

    /*template<typename T> T* GetAsset(std::string relative_path){
        Asset* assetClass = get_asset(relative_path);

        if (assetClass == NULL || assetClass->getType() != TEXTURE) return NULL;

        T* assetUpcast = static_cast<T *>(assetClass);

        if (assetUpcast) return assetUpcast;

        return NULL;
    }*/

    class Asset
    {
        AssetType type;
        std::string url;

    public:
      Asset(AssetType type, std::string url);
      AssetType getType();
      std::string getUrl();

    };

}

#endif
