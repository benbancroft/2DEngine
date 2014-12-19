#include "asset.h"
#include "asset_utils.h"
#include "texture.h"

using namespace Assets;

Asset::Asset(AssetType type, std::string url)
{
  this->type = type;
  this->url = url;
}

AssetType Asset::getType()
{
  return this->type;
}
std::string Asset::getUrl()
{
  return this->url;
}

/*template<typename T> T* GetAsset(std::string relative_path){
    Asset* assetClass = get_asset(relative_path);

    if (assetClass == NULL || assetClass->getType() != TEXTURE) return NULL;

    T* assetUpcast = static_cast<T *>(assetClass);

    if (assetUpcast) return assetUpcast;

    return NULL;
}*/
